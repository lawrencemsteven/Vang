#version 460 core
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D screen;

struct Camera {
    vec3 position;
    vec3 forward;
    vec3 up;
    vec3 right;
    float fov;
};

layout(std430) buffer Chunk {
    uint blocks[1048576];
};
layout(std430) buffer Chunk1 {
    uint blocks1[1048576];
};
layout(std430) buffer Chunk2 {
    uint blocks2[1048576];
};
layout(std430) buffer Chunk3 {
    uint blocks3[1048576];
};
layout(std430) buffer Chunk4 {
    uint blocks4[1048576];
};
layout(std430) buffer Chunk5 {
    uint blocks5[1048576];
};
layout(std430) buffer Chunk6 {
    uint blocks6[1048576];
};
layout(std430) buffer Chunk7 {
    uint blocks7[1048576];
};
layout(std430) buffer Chunk8 {
    uint blocks8[1048576];
};
layout(std430) buffer Chunk9 {
    uint blocks9[1048576];
};
layout(std430) buffer Chunk10 {
    uint blocks10[1048576];
};
layout(std430) buffer Chunk11 {
    uint blocks11[1048576];
};
layout(std430) buffer Chunk12 {
    uint blocks12[1048576];
};
layout(std430) buffer Chunk13 {
    uint blocks13[1048576];
};
layout(std430) buffer Chunk14 {
    uint blocks14[1048576];
};
layout(std430) buffer Chunk15 {
    uint blocks15[1048576];
};

uniform ivec2 iResolution;
uniform float iTime;
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

    //if (coord.y == 63) {
    //    return 2;
    //}
    //coord = coord % 63;


    uint index = coord.x + (64 * coord.z) + (64 * 64 * coord.y);

    return blocks[index];
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
    /*if (pixel_coords*2 == iResolution) {
        imageStore(screen, pixel_coords, vec4(0.0f, 1.0f, 0.0f, 1.0f));
        return;
    }*/

    vec2 uv = (pixel_coords - 0.5*iResolution) / iResolution.y;

    vec3 col = vec3(0);

    vec3 rayOrigin = camera.position;
    vec3 rayDirection = normalize(uv.x*camera.right + uv.y*camera.up + (90/camera.fov)*camera.forward);

    // Positive X to the right
    // Positive Y up
    // Positive Z forward
    // Plane-Assisted Ray Marching
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
        blockSteps += 1;
    }

    if (currentBlock == 1) {
        col = vec3(0.0f, 0.6f, 0.0f);
    } else {
        col = vec3(0.53f, 0.81f, 0.92f);
    }

    col = mix(col, vec3(0.8, 0.8, 0.8), clamp(fogAmount / 8.0f, 0.0f, 1.0f));
    //col = mix(col, vec3(0.8, 0.0, 0.0), fogAmount / 16.0f);

    if (blocks[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks1[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks2[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks3[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks4[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks5[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks6[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks7[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks8[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks9[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks10[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks11[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks12[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks13[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks14[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }
    if (blocks15[1048575] == 0) {
        col = vec3(0.0f, 1.0f, 0.0f);
    }

    imageStore(screen, pixel_coords, vec4(col, 1.0f));
}