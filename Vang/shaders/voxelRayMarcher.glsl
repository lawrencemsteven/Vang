#version 460 core
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform writeonly image2D screen;
layout(r32ui, binding = 1) uniform readonly uimage3D blocks;

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

uniform uint entityCount;

ivec3 getBlockCoords(vec3 pos) {
	return ivec3(round(pos.x), round(pos.y), round(pos.z));
}
vec3 getBlockCoordsFloat(vec3 pos) {
	return vec3(round(pos.x), round(pos.y), round(pos.z));
}
uint getBlock(ivec3 coord) {
	// TODO: Add more chunks
	if (coord.x > 511 || coord.x < 0 || coord.y > 511 || coord.y < 0 || coord.z > 511 || coord.z < 0) {
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

void main() {
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	// Center Pixel
	if (pixel_coords*2 == iResolution) {
		imageStore(screen, pixel_coords, vec4(1.0f, 0.0f, 0.0f, 1.0f));
		return;
	}

	vec2 uv = (pixel_coords - 0.5*iResolution) / iResolution.y;

	vec3 col = vec3(0);

	vec3 rayOrigin = camera.position;
	vec3 rayDirection = normalize(uv.x*camera.right + uv.y*camera.up + (90/camera.fov)*camera.forward);

	// Positive X to the right
	// Positive Y up
	// Positive Z forward
	// Plane-Assisted Ray Marching
	float totalDistance = 0.0f;
	uint currentBlock = 1;
	ivec3 currentBlockPos = getBlockCoords(rayOrigin);
	int blockSteps = 0;
	float fogAmount = 0.0f;
	bool entityHit = false;
	while ((currentBlock == 1 || currentBlock == 2) && blockSteps < 2048 && !entityHit) {
		vec3 signedDirection = sign(rayDirection);

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

		entityHit = entityCheck(rayOrigin, rayDirection, minDist);
		if (!entityHit) {
			currentBlockPos += distDir;
			currentBlock = getBlock(currentBlockPos);
			rayOrigin += rayDirection * minDist;
			totalDistance += minDist;
			blockSteps += 1;
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

	col = mix(col, vec3(0.8, 0.8, 0.8), clamp(fogAmount / 8.0f, 0.0f, 1.0f));
	//col = mix(col, vec3(0.8, 0.0, 0.0), fogAmount / 16.0f);

	// int start = 0;
	// int end = 4;

	// col = vec3(1.0, 0.0, 0.0);
	// for (int i = start; i < end; i++) {
	//     for (int j = start; j < end; j++) {
	//         for (int k = start; k < end; k++) {
	//             if (imageLoad(blocks, ivec3(i, j, k)).r != 0) {
	//                 col = vec3(0.0, 1.0, 0.0);
	//             }
	//         }
	//     }
	// }    

	// if (imageLoad(blocks, ivec3(0,0,64)).r == 10) {
	//     col *= vec3(0.5, 1.0, 0.5);
	// } else {
	//     col *= vec3(1.0, 0.5, 0.5);
	// }

	col = mix(col, col* 0.4, clamp(totalDistance / 20.0f, 0.0f, 1.0f));

	imageStore(screen, pixel_coords, vec4(col, 1.0f));
}