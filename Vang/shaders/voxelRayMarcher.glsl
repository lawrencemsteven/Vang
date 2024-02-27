#version 460 core
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform writeonly image2D screen;
layout(r32ui, binding = 1) uniform readonly uimage3D blocks;
// layout(r32ui, binding = 2) uniform readonly uimage3D chunks;

// layout(std430) buffer Chunk {
//     uint blocks[262144];
// };

struct Camera {
    vec3 position;
    vec3 forward;
    vec3 up;
    vec3 right;
    float fov;
};

struct Light {
    //vec3 position;
    //float range;
    float intensity;
};

struct Entity {
    vec3 position;
    uint radius;
};

layout(std430, binding = 2) buffer Lights {
    Light lights[];
};

layout(std430) buffer Entities {
    Entity entities[];
};

uniform ivec2 iResolution;
uniform float iTime;
uniform uint iRenderDistance;
uniform Camera camera;

ivec3 getBlockCoords(vec3 pos) {
    return ivec3(round(pos.x), round(pos.y), round(pos.z));
}
vec3 getBlockCoordsFloat(vec3 pos) {
    return vec3(round(pos.x), round(pos.y), round(pos.z));
}
uint getBlock(ivec3 coord) {
    // TODO: Add more chunks
    // if (coord.x > 63 || coord.x < 0 ||coord.y > 63 || coord.y < 0 || coord.z > 63 || coord.z < 0) {
    //     return 2;
    // }
    
    // coord = clamp(coord, 0, 63);

    if (coord.y == 63) {
       return 2;
    }
    coord = coord % 63;


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
    uint currentBlock = 0;
    ivec3 currentBlockPos = getBlockCoords(rayOrigin);
    int blockSteps = 0;
    float fogAmount = 0.0f;
    while ((currentBlock == 0 || currentBlock == 3) && blockSteps < 1000) {
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

        if (currentBlock == 3) {
            fogAmount += minDist;
        }

        currentBlockPos += distDir;
        currentBlock = getBlock(currentBlockPos);
        rayOrigin += rayDirection * minDist;
        totalDistance += minDist;
        blockSteps += 1;
    }

    if (currentBlock == 1) {
        col = vec3(0.0f, 0.6f, 0.0f);
    } else if (currentBlock == 4) {
        col = vec3(1.0f, 1.0f, 0.0f);
    } else {
        col = vec3(0.53f, 0.81f, 0.92f);
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

    // if (lights.length() != 0) {
    //     col *= vec3(0.5, 1.0, 0.5);
    // } else {
    //     col *= vec3(1.0, 0.5, 0.5);
    // }

    col = mix(col, col* 0.4, clamp(totalDistance / 20.0f, 0.0f, 1.0f));

    imageStore(screen, pixel_coords, vec4(col, 1.0f));
}