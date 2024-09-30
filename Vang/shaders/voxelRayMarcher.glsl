#version 460 core
precision highp float;
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform writeonly image2D screen;
layout(rg32ui, binding = 1) uniform readonly uimage3D blocks;




///////////////
// Constants //
///////////////
const highp float NOISE_GRANULARITY = 0.5/255.0;
const float MAX_RAYMARCH_STEPS = 256;
const float BRIGHTNESS = 0.01;
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

struct Entity {
	vec4 position;
	float radius;
};

struct Light {
	vec4 positionAndRadius;
	vec4 colorAndIntensity;
};




///////////
// SSBOs //
///////////
layout(std430, binding = 0) readonly buffer Entities {
	Entity entities[];
};

layout(std430, binding = 1) readonly buffer SSBO_LIGHTS {
	Light lights[2];
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
uniform uint LIGHT_COUNT;




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
	vec3 hitPosition;
	uvec2 blockHit;
	ivec3 blockHitPosition;
	float dist;
	vec3 glassAbsorbtion;
	vec3 fogAccumulation;
	vec3 surfaceNormal;
};

bool blockIsTransparent(uvec2 block) {
	return block.r == 1 || block.r == 2 || block.r == 15;
}

bool blockIsSolid(uvec2 block) {
	return !blockIsTransparent(block);
}

// marchStep()
// Meant to represent one iteration of a raymarch
//
// inout vec3 rayOrigin - The origin point of the raymarch
// inout vec3 rayDirection - The NORMALIZED direction to march in
// inout float currMarchDistance - The distance of the overall march (will be accumulated)
// inout uvec3 currBlock - The current block that the rayOrigin is inside of
// inout ivec3 currBlockPos - The current block position that the rayOrigin is inside of
// inout vec3 glassAbsorbtion - The multiplier for the color absorbed by the glass
// inout vec3 fogAccumulation - Basically the opposite of glassAbsorbtion and will add to the color based on the fog.
void marchStep(inout vec3 rayOrigin, inout vec3 rayDirection, inout float currMarchDistance, inout uvec2 currBlock, inout ivec3 currBlockPos, inout vec3 glassAbsorbtion, inout vec3 fogAccumulation, inout vec3 surfaceNormal, bool refractions) {
	vec3 signedDirection = sign(rayDirection);

	ivec3 distDir = ivec3(round(signedDirection.x), 0, 0);
	float cuboidModifier = signedDirection.x > 0 ? getCuboidPositiveX(currBlock.g) : -1 * float(getCuboidNegativeX(currBlock.g));
	vec3 planeOrigin = vec3(float(currBlockPos.x) + 0.5f * signedDirection.x + cuboidModifier, currBlockPos.yz);
	vec3 planeNormal = vec3(-sign(rayDirection.x), 0.0f, 0.0f);
	float minDist = planeIntersectionDistance(rayOrigin, rayDirection, planeOrigin, planeNormal);

	cuboidModifier = signedDirection.y > 0 ? getCuboidPositiveY(currBlock.g) : -1 * float(getCuboidNegativeY(currBlock.g));
	planeOrigin = vec3(currBlockPos.x, float(currBlockPos.y) + 0.5f * signedDirection.y + cuboidModifier, currBlockPos.z);
	planeNormal = vec3(0.0f, -sign(rayDirection.y), 0.0f);
	float newDist = planeIntersectionDistance(rayOrigin, rayDirection, planeOrigin, planeNormal);
	if (newDist < minDist) {
		distDir = ivec3(0, round(signedDirection.y), 0);
		minDist = newDist;
	}
	cuboidModifier = signedDirection.z > 0 ? getCuboidPositiveZ(currBlock.g) : -1 * float(getCuboidNegativeZ(currBlock.g));
	planeOrigin = vec3(currBlockPos.xy, float(currBlockPos.z) + 0.5f * signedDirection.z + cuboidModifier);
	planeNormal = vec3(0.0f, 0.0f, -sign(rayDirection.z));
	newDist = planeIntersectionDistance(rayOrigin, rayDirection, planeOrigin, planeNormal);
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
		glassAbsorbtion += minDist * vec3(1.0, 1.0, 0.1);
	}

	rayOrigin += rayDirection * minDist;
	currBlockPos = getBlockCoords(rayOrigin + 0.5 * distDir);
	uvec2 previousBlock = currBlock;
	currBlock = getBlockInfo(currBlockPos);
	currMarchDistance += minDist;

	surfaceNormal = -vec3(distDir);
	if (refractions) {
		if (currBlock.r == 15 && previousBlock.r != 15) { // Going into glass
			rayDirection = lightRefract(rayDirection, surfaceNormal, glassRefractionIndex);
		} else if (previousBlock.r == 15 && currBlock.r != 15) { // Coming out of glass
			rayDirection = lightRefract(rayDirection, surfaceNormal, glassRefractionIndex);
		}
	}
}

RaymarchReturn marchToPoint(vec3 rayOrigin, vec3 pos) {
	float maxMarchDistance = length(pos - rayOrigin);

	vec3 rayDirection = normalize(pos - rayOrigin);
	float totalDistance = 0.0;
	ivec3 currBlockPos = getBlockCoords(rayOrigin);
	uvec2 currBlock = getBlockInfo(currBlockPos);
	vec3 glassAbsorbtion = vec3(0.0);
	vec3 fogAccumulation = vec3(0.0);
	vec3 surfaceNormal = vec3(0.0);

	int raymarchIterations = 0;
	while (totalDistance < maxMarchDistance && blockIsTransparent(currBlock) && raymarchIterations < MAX_RAYMARCH_STEPS) {
		marchStep(rayOrigin, rayDirection, totalDistance, currBlock, currBlockPos, glassAbsorbtion, fogAccumulation, surfaceNormal, false);
		raymarchIterations += 1;
	}

	return RaymarchReturn(totalDistance < maxMarchDistance && blockIsSolid(currBlock), rayOrigin, currBlock, currBlockPos, totalDistance, glassAbsorbtion, fogAccumulation, surfaceNormal);
}

RaymarchReturn marchUntilHit(vec3 rayOrigin, vec3 rayDirection) {
	float totalDistance = 0.0;
	ivec3 currBlockPos = getBlockCoords(rayOrigin);
	uvec2 currBlock = getBlockInfo(currBlockPos);
	vec3 glassAbsorbtion = vec3(0.0);
	vec3 fogAccumulation = vec3(0.0);
	vec3 surfaceNormal = vec3(0.0);

	int raymarchIterations = 0;
	while (blockIsTransparent(currBlock) && raymarchIterations < MAX_RAYMARCH_STEPS) {		
		marchStep(rayOrigin, rayDirection, totalDistance, currBlock, currBlockPos, glassAbsorbtion, fogAccumulation, surfaceNormal, true);
		raymarchIterations += 1;
	}

	return RaymarchReturn(blockIsSolid(currBlock), rayOrigin, currBlock, currBlockPos, totalDistance, glassAbsorbtion, fogAccumulation, surfaceNormal);
}

vec3 marchLights(vec3 surfaceColor, vec3 rayOrigin, vec3 rayDirection, vec3 surfaceNormal) {
	// Ambient
	vec3 ambient = BRIGHTNESS * surfaceColor;
	vec3 outColor = vec3(0.0);

	for (int i = 0; i < LIGHT_COUNT; i++) {
		// Check light distance
		if (lights[i].positionAndRadius.w < distance(lights[i].positionAndRadius.xyz, rayOrigin)) {
			continue;
		}

		// Shadow
		RaymarchReturn rayInfo = marchToPoint(rayOrigin + (surfaceNormal * 0.0001), lights[i].positionAndRadius.xyz);
		if (rayInfo.hit) {
			continue;
		}

		// Diffuse
		vec3 lightDir = normalize(lights[i].positionAndRadius.xyz - rayOrigin);
		float diff = max(dot(surfaceNormal, lightDir), 0.0);
		vec3 diffuse = lights[i].colorAndIntensity.xyz * diff * surfaceColor;

		// Specular
		vec3 halfwayDir = normalize(lightDir + -rayDirection);
		float spec = pow(max(dot(surfaceNormal, halfwayDir), 0.0), /*MATERIAL_SHININESS*/ 128);
		// TODO: Should specular include surface color???
		vec3 specular = lights[i].colorAndIntensity.xyz * spec * surfaceColor;

		// Attenuation
		float dist = length(lights[i].positionAndRadius.xyz - rayOrigin);
		float attenuation = clamp(1.0 - dist / lights[i].positionAndRadius.w, 0.0, 1.0);

		// Apply Attenuation
		outColor += (ambient + diffuse + specular) * attenuation * exp(-rayInfo.glassAbsorbtion);
	}

	return max(outColor, BRIGHTNESS * surfaceColor);
}




//////////////////////
// Block Coloration //
//////////////////////
vec3 getBlockColor(uvec2 block) {
	vec3 outputColor = vec3(0.0);

	// TODO: Put this into a lookup
	if (block.r == 0) {            // Void
		outputColor = vec3(0.0f, 0.0f, 0.0f);
	} else if (block.r == 3) {      // Black
		outputColor = vec3(0.1f, 0.1f, 0.1f);
	} else if (block.r == 4) {		// Gray
		outputColor = vec3(0.35f, 0.35f, 0.35f);
	} else if (block.r == 5) {		// LightGray
		outputColor = vec3(0.7f, 0.7f, 0.7f);
	} else if (block.r == 6) {		// White
		outputColor = vec3(0.95f, 0.95f, 0.95f);
	} else if (block.r == 7) {		// Red
		outputColor = vec3(0.8f, 0.1f, 0.1f);
	} else if (block.r == 8) {		// Orange
		outputColor = vec3(0.8f, 0.4f, 0.1f);
	} else if (block.r == 9) {		// Yellow
		outputColor = vec3(0.8f, 0.8f, 0.1f);
	} else if (block.r == 10) {		// Green
		outputColor = vec3(0.1f, 0.7f, 0.1f);
	} else if (block.r == 11) {		// Blue
		outputColor = vec3(0.1f, 0.1f, 0.8f);
	} else if (block.r == 12) {		// Purple
		outputColor = vec3(0.5f, 0.1f, 0.8f);
	} else if (block.r == 13) {		// Pink
		outputColor = vec3(0.9f, 0.5f, 0.6f);
	} else if (block.r == 14) {		// Rainbow
		const float totalRainbowTime = 10.0f;
		const float segmentTime = totalRainbowTime / 3.0f;
		const int animationState = int(3.0f * (mod(iTime, totalRainbowTime) / totalRainbowTime));
		const float animationAmount = mod(iTime, segmentTime) / segmentTime;

		if (animationState == 0) {
			outputColor = vec3(1.0f - animationAmount, animationAmount, 0.0f);
		} else if (animationState == 1) {
			outputColor = vec3(0.0f, 1.0f - animationAmount, animationAmount);
		} else if (animationState == 2) {
			outputColor = vec3(animationAmount, 0.0f, 1.0f - animationAmount);
		}
	}

	return outputColor;
}

bool drawOutline(vec3 rayOrigin, ivec3 blockPos) {
	// Selected Block Outline
	// TODO: Get to work with glass (shader marches through glass,
	// 		 outline is selected block, glass can't be selected)
	// TODO: If pixel is black, just return
	if (selectedBlock.w == 1 && blockPos == selectedBlock.xyz) {
		const float vertexWidth = 0.05f;
		const float outlineWidth = 0.02f;

		// Vertices
		bool xBound = fract(rayOrigin.x) > 0.5f - vertexWidth && fract(rayOrigin.x) < 0.5f + vertexWidth;
		bool yBound = fract(rayOrigin.y) > 0.5f - vertexWidth && fract(rayOrigin.y) < 0.5f + vertexWidth;
		bool zBound = fract(rayOrigin.z) > 0.5f - vertexWidth && fract(rayOrigin.z) < 0.5f + vertexWidth;

		if (xBound && yBound && zBound) {
			return true;
		}

		// Edges
		xBound = fract(rayOrigin.x) > 0.5f - outlineWidth && fract(rayOrigin.x) < 0.5f + outlineWidth;
		yBound = fract(rayOrigin.y) > 0.5f - outlineWidth && fract(rayOrigin.y) < 0.5f + outlineWidth;
		zBound = fract(rayOrigin.z) > 0.5f - outlineWidth && fract(rayOrigin.z) < 0.5f + outlineWidth;

		return xBound && yBound || yBound && zBound || zBound && xBound;
	}

	return false;
}

vec3 getPixelColor(vec3 rayOrigin, uvec2 block, ivec3 blockPos) {
	if (drawOutline(rayOrigin, blockPos)) {
		return vec3(0.0);
	}

	return getBlockColor(block);
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


	// Ray March From Camera
	RaymarchReturn rayInfo = marchUntilHit(rayOrigin, rayDirection);

	rayOrigin = rayInfo.hitPosition;
	uvec2 currBlock = rayInfo.blockHit;
	ivec3 currBlockPos = rayInfo.blockHitPosition;
	float totalDistance = rayInfo.dist;
	vec3 glassAbsorbtion = rayInfo.glassAbsorbtion;
	vec3 fogAccumulation = rayInfo.fogAccumulation;
	vec3 surfaceNormal = rayInfo.surfaceNormal;


	// Get Base Pixel Color
	col = getPixelColor(rayOrigin, currBlock, currBlockPos);


	// Calculate Fog Amount
	col = clamp(col + fogAccumulation, 0.0, 1.0);


	// Calculate Glass Amount
	col *= exp(-glassAbsorbtion);

	
	// Lights
	col = marchLights(col, rayOrigin, rayDirection, surfaceNormal);


	// Fix Color Banding
	col += mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(uv));

	// Return value
	imageStore(screen, pixel_coords, vec4(col, 1.0f));
}