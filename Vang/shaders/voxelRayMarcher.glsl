#version 460 core
precision highp float;
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform writeonly image2D screen;
layout(rg32ui, binding = 1) uniform readonly uimage3D blocks;




///////////////
// Constants //
///////////////
const highp float NOISE_GRANULARITY = 0.5/255.0;
const float airRefractionIndex = 1.0;
const float glassRefractionIndex = 1.52;




///////////////////////
// Common Structures //
///////////////////////
struct Camera {
	vec3 position;
	vec3 forward;
	vec3 up;
	vec3 right;
	float fov;
};

struct Light {
	vec4 positionAndRadius;
	vec4 colorAndIntensity;
};

struct Entity {
	vec4 position;
	float radius;
};




///////////
// SSBOs //
///////////
layout(std430) readonly buffer Lights {
	Light lights[];
};

layout(std430) readonly buffer Entities {
	Entity entities[];
};




//////////////
// Uniforms //
//////////////
uniform ivec2 iResolution;
uniform float iTime;
uniform uint iRenderDistance;

uniform Camera camera;

uniform ivec4 selectedBlock;
uniform uint entityCount;
uniform uint lightCount;




/////////////////////////////
// Block Helping Functions //
/////////////////////////////
ivec3 getBlockCoords(vec3 pos) {
	return ivec3(round(pos.x), round(pos.y), round(pos.z));
}

vec3 getBlockCoordsFloat(vec3 pos) {
	return vec3(round(pos.x), round(pos.y), round(pos.z));
}

uvec2 getBlockInfo(ivec3 coord) {
	// TODO: Add more chunks
	if (coord.x > 575 || coord.x < 0 || coord.y > 575 || coord.y < 0 || coord.z > 575 || coord.z < 0) {
		return uvec2(0, 0x2108421);
	}

	// TODO: This should not be here
	coord.yz = coord.zy;

	return imageLoad(blocks, coord).rg;
}

uvec2 getBlockInfo(vec3 pos) {
	return getBlockInfo(getBlockCoords(pos));
}




/////////////
// Cuboids //
/////////////
//
// 00 00000 00000 00000 00000 00000 00000
//  1   2     3     4     5     6     7
//
// Todo: First bit should be transparency
//
// 1 = Block Information
//
// 2 = +X
// 3 = -X
//
// 4 = +Y
// 5 = -Y
//
// 6 = +Z
// 7 = -Z
//
uint cuboidBitShift(uint cuboidInfo, uint shiftAmount) {
	return cuboidInfo >> shiftAmount & 0x1F;
}
uint getCuboidPositiveX(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 25);
}
uint getCuboidNegativeX(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 20);
}
uint getCuboidPositiveY(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 15);
}
uint getCuboidNegativeY(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 10);
}
uint getCuboidPositiveZ(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 5);
}
uint getCuboidNegativeZ(uint cuboidInfo) {
	return cuboidBitShift(cuboidInfo, 0);
}




/////////////////////////////
// Reflection & Refraction //
/////////////////////////////
// TODO: Reflection

vec3 lightRefract(const vec3 I, const vec3 N, const float ior)
{
    float cosi = clamp(-1, 1, dot(I, N));
    float etai = 1;
	float etat = ior;
    vec3 n = N;
    if (cosi < 0) { 
		cosi = -cosi; 
	} else {
		float temp = etai;
		etai = etat;
		etat = temp;
		n = -N;
	}
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);

	if (k < 0) {
		return vec3(0);
	} else {
		return eta * I + (eta * cosi - sqrt(k)) * n;
	}
}




//////////////////
// Ray Marching //
//////////////////
float planeIntersectionDistance(vec3 rayOrigin, vec3 rayDirection, vec3 planeOrigin, vec3 planeNormal) {
	float denom = dot(planeNormal, rayDirection);
	if (abs(denom) > 0.0f) {
		vec3 pointDist = planeOrigin - rayOrigin;
		float dist = dot(pointDist, planeNormal) / denom;
		return dist;
	}
	// Large enough for a miss
	// Might never be reached???
	// TODO: Think this over
	return 100.0f;
}

struct RaymarchReturn {
	bool hit;
	uint blockHit;
	ivec3 blockHitPosition;
	float dist;
};

bool blockIsTransparent(uint block) {
	return block == 1 || block == 2 || block == 15;
}

bool blockIsSolid(uint block) {
	return !blockIsTransparent(block);
}

// marchStep()
// Meant to represent one iteration of a raymarch
//
// inout vec3 origin - The origin point of the raymarch
// inout vec3 direction - The NORMALIZED direction to march in
// inout float currMarchDistance - The distance of the overall march (will be accumulated)
// inout uvec3 currBlock - The current block that the origin is inside of
// inout ivec3 currBlockPos - The current block position that the origin is inside of
// inout vec3 glassAbsorbtion - The multiplier for the color absorbed by the glass
// inout vec3 fogAccumulation - Basically the opposite of glassAbsorbtion and will add to the color based on the fog.
//
// TODO: currBlock can be solved for with origin???
// TODO: fogAccumulation is not correct (should fog be lit if in complete darkness?)
//		 Proper Volumetric Fog should be considered here
void marchStep(inout vec3 origin, inout vec3 direction, inout float currMarchDistance, inout uvec2 currBlock, inout ivec3 currBlockPos, inout vec3 glassAbsorbtion, inout vec3 fogAccumulation) {
	vec3 signedDirection = sign(direction);

	ivec3 distDir = ivec3(round(signedDirection.x), 0, 0);
	float cuboidModifier = signedDirection.x > 0 ? getCuboidPositiveX(currBlock.g) : -1 * float(getCuboidNegativeX(currBlock.g));
	vec3 planeOrigin = vec3(float(currBlockPos.x) + 0.5f * signedDirection.x + cuboidModifier, currBlockPos.yz);
	vec3 planeNormal = vec3(-sign(direction.x), 0.0f, 0.0f);
	float minDist = planeIntersectionDistance(origin, direction, planeOrigin, planeNormal);

	cuboidModifier = signedDirection.y > 0 ? getCuboidPositiveY(currBlock.g) : -1 * float(getCuboidNegativeY(currBlock.g));
	planeOrigin = vec3(currBlockPos.x, float(currBlockPos.y) + 0.5f * signedDirection.y + cuboidModifier, currBlockPos.z);
	planeNormal = vec3(0.0f, -sign(direction.y), 0.0f);
	float newDist = planeIntersectionDistance(origin, direction, planeOrigin, planeNormal);
	if (newDist < minDist) {
		distDir = ivec3(0, round(signedDirection.y), 0);
		minDist = newDist;
	}
	cuboidModifier = signedDirection.z > 0 ? getCuboidPositiveZ(currBlock.g) : -1 * float(getCuboidNegativeZ(currBlock.g));
	planeOrigin = vec3(currBlockPos.xy, float(currBlockPos.z) + 0.5f * signedDirection.z + cuboidModifier);
	planeNormal = vec3(0.0f, 0.0f, -sign(direction.z));
	newDist = planeIntersectionDistance(origin, direction, planeOrigin, planeNormal);
	if (newDist < minDist) {
		distDir = ivec3(0, 0, round(signedDirection.z));
		minDist = newDist;
	}

	// Fog
	if (currBlock.r == 2) {
		fogAccumulation += minDist * vec3(0.0625, 0.0625, 0.0625);
	}

	// Glass
	if (currBlock.r == 15) {
		// TODO: Look over glass values
		glassAbsorbtion += minDist * vec3(1.0, 0.0, 0.0);
	}

	origin += direction * minDist;
	currBlockPos = getBlockCoords(origin + 0.5 * distDir);
	uvec2 previousBlock = currBlock;
	currBlock = getBlockInfo(currBlockPos);
	currMarchDistance += minDist;

	if (currBlock.r == 15 && previousBlock.r != 15) { // Going into glass
		const vec3 normal = -vec3(distDir);
		direction = lightRefract(direction, normal, glassRefractionIndex);
	} else if (previousBlock.r == 15 && currBlock.r != 15) { // Coming out of glass
		const vec3 normal = -vec3(distDir);
		direction = lightRefract(direction, normal, glassRefractionIndex);
	}
}

RaymarchReturn marchToPoint(vec3 origin, vec3 pos) {
	float maxMarchDistance = length(pos - origin);
	float currMarchDistance = 0.0;

	while (currMarchDistance < maxMarchDistance) {

	}

	return RaymarchReturn(true, 1, ivec3(0,0,0), 1.0);
}

RaymarchReturn marchUntilHit(vec3 origin, vec3 direction) {
	return RaymarchReturn(true, 1, ivec3(0,0,0), 1.0);
}




//////////////
// Entities //
//////////////
float distanceToNearestEntity(const vec3 rayOrigin) {
	float minDist = 1024.0f;
	for (int i = 0; i < entityCount; i++) {
		minDist = min(minDist, length(entities[i].position.xyz - rayOrigin) - entities[i].radius);
	}
	return minDist;
}

bool entityCheck(vec3 rayOrigin, const vec3 rayDirection, float minBlockDist) {
	while (minBlockDist > 0.0f) {
		float dist = distanceToNearestEntity(rayOrigin);
		minBlockDist -= dist;
		rayOrigin += rayDirection * dist;
		if (dist < 0.01f) {
			return true;
		}
	}
	return false;
}




////////////////////////////
// Random Value Functions //
////////////////////////////
highp float random(highp vec2 coords) {
   return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}




///////////////////
// Main Function //
///////////////////
void main() {
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	vec2 uv = (pixel_coords - 0.5*iResolution) / iResolution.y;

	vec3 col = vec3(0);

	const float crosshairSize = 0.005f;
	if (length(uv) < crosshairSize) {
		imageStore(screen, pixel_coords, vec4(0.0f, 0.0f, 0.0f, 1.0f));
		return;
	}

	vec3 rayOrigin = camera.position;
	vec3 rayDirection = normalize(uv.x*camera.right + uv.y*camera.up + (90/camera.fov)*camera.forward);

	// Positive X to the right
	// Positive Y up
	// Positive Z forward
	// Plane-Assisted Ray Marching
	float totalDistance = 0.0f;
	ivec3 currentBlockPos = getBlockCoords(rayOrigin);
	uvec2 previousBlock = getBlockInfo(currentBlockPos);
	uvec2 currentBlock = previousBlock;
	int raymarchIterations = 0;
	float fogAmount = 0.0f;
	float glassAmount = 0.0f;
	vec3 glassAbsorbtion = vec3(0.0);
	vec3 fogAccumulation = vec3(0.0);
	while ((currentBlock.r == 1 || currentBlock.r == 2 || currentBlock.r == 15) && raymarchIterations < 256) {		
		marchStep(rayOrigin, rayDirection, totalDistance, currentBlock, currentBlockPos, glassAbsorbtion, fogAccumulation);
		raymarchIterations += 1;
	}


	// Block Colors
	// TODO: Put this into a lookup
	if (currentBlock.r == 0) {            // Void
		col = vec3(0.0f, 0.0f, 0.0f);
	}else if (currentBlock.r == 3) {      // Black
		col = vec3(0.1f, 0.1f, 0.1f);
	} else if (currentBlock.r == 4) {		// Gray
		col = vec3(0.35f, 0.35f, 0.35f);
	} else if (currentBlock.r == 5) {		// LightGray
		col = vec3(0.7f, 0.7f, 0.7f);
	} else if (currentBlock.r == 6) {		// White
		col = vec3(0.95f, 0.95f, 0.95f);
	} else if (currentBlock.r == 7) {		// Red
		col = vec3(0.8f, 0.1f, 0.1f);
	} else if (currentBlock.r == 8) {		// Orange
		col = vec3(0.8f, 0.4f, 0.1f);
	} else if (currentBlock.r == 9) {		// Yellow
		col = vec3(0.8f, 0.8f, 0.1f);
	} else if (currentBlock.r == 10) {	// Green
		col = vec3(0.1f, 0.7f, 0.1f);
	} else if (currentBlock.r == 11) {	// Blue
		col = vec3(0.1f, 0.1f, 0.8f);
	} else if (currentBlock.r == 12) {	// Purple
		col = vec3(0.5f, 0.1f, 0.8f);
	} else if (currentBlock.r == 13) {	// Pink
		col = vec3(0.9f, 0.5f, 0.6f);
	} else if (currentBlock.r == 14) {	// Rainbow
		const float totalRainbowTime = 10.0f;
		const float segmentTime = totalRainbowTime / 3.0f;
		const int animationState = int(3.0f * (mod(iTime, totalRainbowTime) / totalRainbowTime));
		const float animationAmount = mod(iTime, segmentTime) / segmentTime;

		if (animationState == 0) {
			col = vec3(1.0f - animationAmount, animationAmount, 0.0f);
		} else if (animationState == 1) {
			col = vec3(0.0f, 1.0f - animationAmount, animationAmount);
		} else if (animationState == 2) {
			col = vec3(animationAmount, 0.0f, 1.0f - animationAmount);
		}
	}

	// Selected Block Outline
	// TODO: Get to work with glass (shader marches through glass,
	// 		 outline is selected block, glass can't be selected)
	if (selectedBlock.a == 1 && currentBlockPos == selectedBlock.xyz) {
		const float vertexWidth = 0.05f;
		const float outlineWidth = 0.02f;

		// Vertices
		bool xBound = fract(rayOrigin.x) > 0.5f - vertexWidth && fract(rayOrigin.x) < 0.5f + vertexWidth;
		bool yBound = fract(rayOrigin.y) > 0.5f - vertexWidth && fract(rayOrigin.y) < 0.5f + vertexWidth;
		bool zBound = fract(rayOrigin.z) > 0.5f - vertexWidth && fract(rayOrigin.z) < 0.5f + vertexWidth;

		if (xBound && yBound && zBound) {
			col = vec3(0.0f, 0.0f, 0.0f);
		}

		// Edges
		xBound = fract(rayOrigin.x) > 0.5f - outlineWidth && fract(rayOrigin.x) < 0.5f + outlineWidth;
		yBound = fract(rayOrigin.y) > 0.5f - outlineWidth && fract(rayOrigin.y) < 0.5f + outlineWidth;
		zBound = fract(rayOrigin.z) > 0.5f - outlineWidth && fract(rayOrigin.z) < 0.5f + outlineWidth;

		if (xBound && yBound || yBound && zBound || zBound && xBound) {
			col = vec3(0.0f, 0.0f, 0.0f);
		}
	}


	// Calculate Fog Amount
	col = clamp(col + fogAccumulation, 0.0, 1.0);


	// Calculate Glass Amount
	col *= exp(-glassAbsorbtion);
	

	// Headlight
	col = mix(col, col* 0.4, clamp(totalDistance / 20.0f, 0.0f, 1.0f));


	// Fix Color Banding
	col += mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(uv));


	// Return value
	imageStore(screen, pixel_coords, vec4(col, 1.0f));
}