#version 460 core
precision highp float;
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform writeonly image2D screen;
layout(r32ui, binding = 1) uniform readonly uimage3D blocks;

const highp float NOISE_GRANULARITY = 0.5/255.0;
const float airRefractionIndex = 1.0;
const float glassRefractionIndex = 1.52;

// enum class Blocks : uint32_t {
// 		Air,
// 		Fog,
// 		Black,
// 		Gray,
// 		LightGray,
// 		White,
// 		Red,
// 		Orange,
// 		Yellow,
// 		Green,
// 		Blue,
// 		Purple,
// };

struct Camera {
	vec3 position;
	vec3 forward;
	vec3 up;
	vec3 right;
	float fov;
};

struct Light {
	vec4 position;
	float range;
	float intensity;
};

struct Entity {
	vec4 position;
	float radius;
};

layout(std430) readonly buffer Lights {
	Light lights[];
};

layout(std430) readonly buffer Entities {
	Entity entities[];
};

uniform ivec2 iResolution;
uniform float iTime;
uniform uint iRenderDistance;
uniform Camera camera;

uniform ivec4 selectedBlock;

uniform uint entityCount;

ivec3 getBlockCoords(vec3 pos) {
	return ivec3(round(pos.x), round(pos.y), round(pos.z));
}
vec3 getBlockCoordsFloat(vec3 pos) {
	return vec3(round(pos.x), round(pos.y), round(pos.z));
}
uint getBlock(ivec3 coord) {
	// TODO: Add more chunks
	if (coord.x > 575 || coord.x < 0 || coord.y > 575 || coord.y < 0 || coord.z > 575 || coord.z < 0) {
		return 0;
	}
	
	// coord = clamp(coord, 0, 63);

	// if (coord.y == 63) {
	//    return 2;
	// }
	// coord = coord % 63;


	//uint index = coord.x + (64 * coord.z) + (64 * 64 * coord.y);

	coord.yz = coord.zy;

	// return blocks[index];
	return imageLoad(blocks, coord).r;
}
uint getBlock(vec3 pos) {
	return getBlock(getBlockCoords(pos));
	
}

float planeIntersectionDistance(vec3 rayOrigin, vec3 rayDirection, vec3 planeOrigin, vec3 planeNormal) {
	float denom = dot(planeNormal, rayDirection);
	if (abs(denom) > 0.0f) {
		vec3 pointDist = planeOrigin - rayOrigin;
		float dist = dot(pointDist, planeNormal) / denom;
		return dist;
	}
	// Large enough for a miss
	// Might never be reached???
	return 100.0f;
}

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

highp float random(highp vec2 coords) {
   return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}

vec3 refract(const vec3 I, const vec3 N, const float ior)
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

void main() {
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	// Center Pixel
	// if (pixel_coords*2 == iResolution) {
	// 	imageStore(screen, pixel_coords, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	// 	return;
	// }

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
	uint previousBlock = getBlock(currentBlockPos);
	uint currentBlock = previousBlock;
	int blockSteps = 0;
	float fogAmount = 0.0f;
	float glassAmount = 0.0f;
	bool entityHit = false;
	while ((currentBlock == 1 || currentBlock == 2 || currentBlock == 15) && blockSteps < 2048 && !entityHit) {
		if (rayDirection.x == 0.0 && rayDirection.y == 0.0 && rayDirection.z == 0.0) {
			imageStore(screen, pixel_coords, vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return;
		}
		
		vec3 signedDirection = sign(rayDirection);

		if (signedDirection.x == 0 && signedDirection.y == 0 && signedDirection.z == 0) {
			imageStore(screen, pixel_coords, vec4(0.0f, 0.0f, 1.0f, 1.0f));
			return;
		}

		ivec3 distDir = ivec3(round(signedDirection.x), 0, 0);
		float minDist = planeIntersectionDistance(rayOrigin, rayDirection, vec3(currentBlockPos.x + 0.5f * signedDirection.x, currentBlockPos.yz), vec3(-sign(rayDirection.x), 0.0f, 0.0f));

		float newDist = planeIntersectionDistance(rayOrigin, rayDirection, vec3(currentBlockPos.x, currentBlockPos.y + 0.5f * signedDirection.y, currentBlockPos.z), vec3(0.0f, -sign(rayDirection.y), 0.0f));
		if (newDist < minDist) {
			distDir = ivec3(0, round(signedDirection.y), 0);
			minDist = newDist;
		}
		newDist = planeIntersectionDistance(rayOrigin, rayDirection, vec3(currentBlockPos.xy, currentBlockPos.z + 0.5f * signedDirection.z), vec3(0.0f, 0.0f, -sign(rayDirection.z)));
		if (newDist < minDist) {
			distDir = ivec3(0, 0, round(signedDirection.z));
			minDist = newDist;
		}

		// Fog
		if (currentBlock == 2) {
			fogAmount += minDist;
		}

		// Glass
		if (currentBlock == 15) {
			glassAmount += minDist;
		}

		entityHit = entityCheck(rayOrigin, rayDirection, minDist);
		if (!entityHit) {
			currentBlockPos += distDir;
			previousBlock = currentBlock;
			currentBlock = getBlock(currentBlockPos);
			rayOrigin += rayDirection * minDist;
			totalDistance += minDist;
			blockSteps += 1;

			if (currentBlock == 15 && previousBlock != 15) { // Going into glass
				// const vec3 normal = -vec3(distDir);
				// const float angleOfIncidence = acos(dot(normal, -rayDirection));
				// const float newAngleOfIncidence = asin(sin(angleOfIncidence) * airRefractionIndex / glassRefractionIndex);

				// // Rodrigues Rotation Formula
				// const vec3 v = -normal;
				// const vec3 k = cross(-normal, rayDirection);
				// const float theta = newAngleOfIncidence;
				// rayDirection = normalize(v * cos(theta) + cross(k, v) * sin(theta) + k * dot(k, v) * (1.0 - cos(theta)));

				// float n1 = airRefractionIndex;
				// float n2 = glassRefractionIndex;
				// float n = n1 / n2;
				// vec3 I = rayDirection;
				// vec3 N = -vec3(distDir);
				// float c1 = dot(N, I);
				// float c2 = sqrt(1.0 - (n * n) * (1.0 - c1 * c1));
				// rayDirection = normalize(n * (I + c1 * N) - N * c2);

				const vec3 normal = -vec3(distDir);
				rayDirection = refract(rayDirection, normal, glassRefractionIndex);
			} else if (previousBlock == 15 && currentBlock != 15) { // Coming out of glass
				// const vec3 normal = -vec3(distDir);
				// const float angleOfIncidence = acos(dot(normal, -rayDirection));
				// const float newAngleOfIncidence = asin(sin(angleOfIncidence) * glassRefractionIndex / airRefractionIndex);

				// // Rodrigues Rotation Formula
				// const vec3 v = -normal;
				// const vec3 k = cross(-normal, rayDirection);
				// const float theta = newAngleOfIncidence;
				// rayDirection = normalize(v * cos(theta) + cross(k, v) * sin(theta) + k * dot(k, v) * (1.0 - cos(theta)));

				// float n1 = glassRefractionIndex;
				// float n2 = airRefractionIndex;
				// float n = n1 / n2;
				// vec3 I = rayDirection;
				// vec3 N = -vec3(distDir);
				// float c1 = dot(N, I);
				// float c2 = sqrt(1.0 - (n * n) * (1.0 - c1 * c1));

				// rayDirection = normalize(n * (I + c1 * N) - N * c2);

				// if (abs(dot(rayDirection, rayDirection)) <= 0.01f && abs(dot(rayDirection, rayDirection)) >= 0.0f) {
				// 	imageStore(screen, pixel_coords, vec4(1.0f, 0.0f, 0.0f, 1.0f));
				// 	return;
				// }
				
				const vec3 normal = -vec3(distDir);
				rayDirection = refract(rayDirection, normal, glassRefractionIndex);
			}
		}
	}

	if (currentBlock == 0) {            // Void
		col = vec3(0.0f, 0.0f, 0.0f);
	}else if (currentBlock == 3) {      // Black
		col = vec3(0.1f, 0.1f, 0.1f);
	} else if (currentBlock == 4) {		// Gray
		col = vec3(0.35f, 0.35f, 0.35f);
	} else if (currentBlock == 5) {		// LightGray
		col = vec3(0.7f, 0.7f, 0.7f);
	} else if (currentBlock == 6) {		// White
		col = vec3(0.95f, 0.95f, 0.95f);
	} else if (currentBlock == 7) {		// Red
		col = vec3(0.8f, 0.1f, 0.1f);
	} else if (currentBlock == 8) {		// Orange
		col = vec3(0.8f, 0.4f, 0.1f);
	} else if (currentBlock == 9) {		// Yellow
		col = vec3(0.8f, 0.8f, 0.1f);
	} else if (currentBlock == 10) {	// Green
		col = vec3(0.1f, 0.7f, 0.1f);
	} else if (currentBlock == 11) {	// Blue
		col = vec3(0.1f, 0.1f, 0.8f);
	} else if (currentBlock == 12) {	// Purple
		col = vec3(0.5f, 0.1f, 0.8f);
	} else if (currentBlock == 13) {	// Pink
		col = vec3(0.9f, 0.5f, 0.6f);
	} else if (currentBlock == 14) {	// Rainbow
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
	} else if (entityHit) {				// Entity
		col = vec3(1.0f, 0.0f, 1.0f);
	}

	// TODO: Get to work with glass (shader marches through glass,
	// 		 outline is selected block, glass can't be selected)
	// Selected Block Outline
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
	col = mix(col, vec3(0.8, 0.8, 0.8), clamp(fogAmount / 8.0f, 0.0f, 1.0f));
	//col = mix(col, vec3(0.8, 0.0, 0.0), fogAmount / 16.0f);


	// Calculate Glass Amount
	if (glassAmount > 0.0f) {
		glassAmount += 5.0f;
	}
	col = mix(col, vec3(0.9, 0.0, 0.0), clamp(glassAmount / 20.0f, 0.0f, 1.0f));
	

	// Headlight
	col = mix(col, col* 0.4, clamp(totalDistance / 20.0f, 0.0f, 1.0f));


	// Fix Color Banding
	col += mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(uv));


	// Return value
	imageStore(screen, pixel_coords, vec4(col, 1.0f));
}