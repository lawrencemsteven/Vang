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
    uint blocks[262144];
};

uniform ivec2 iResolution;
uniform float iTime;
uniform Camera camera;

#define MAX_STEPS 100
#define MAX_DIST 100.0f
#define SURF_DIST 0.01f

float getDist(vec3 p) {
    vec4 sphere = vec4(0, sin(iTime)+2, 6, 1);

    float sphere_dist = length(p - sphere.xyz) - sphere.w;
    float plane_dist = p.y;

    float dist = min(sphere_dist, plane_dist);
    return dist;
}

float rayMarch(vec3 rayOrigin, vec3 rayDirection) {
    float dO = 0.0f;
    
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = rayOrigin + rayDirection*dO;
        float dS = getDist(p);
        dO += dS;
        if (dO > MAX_DIST || dS < SURF_DIST) break;
    }

    return dO;
}

vec3 getNormal(vec3 p) {
    float d = getDist(p);
    vec2 e = vec2(0.01, 0);

    vec3 n = d - vec3(
        getDist(p-e.xyy),
        getDist(p-e.yxy),
        getDist(p-e.yyx));
    
    return normalize(n);
}

float getLight(vec3 p) {
    vec3 lightPosition = vec3(0, 5, 10);
    //lightPosition.xz += vec2(sin(iTime), cos(iTime)) * 2.0f;
    vec3 l = normalize(lightPosition - p);
    vec3 n = getNormal(p);

    float dif = clamp(dot(n, l), 0.0f, 1.0f);
    float d = rayMarch(p+n*SURF_DIST*2, l);
    if (d < length(lightPosition - p)) dif *= 0.1f;
    return dif;
}

ivec3 getBlockCoords(vec3 pos) {
    return ivec3(round(pos.x), round(pos.y), round(pos.z));
}
vec3 getBlockCoordsFloat(vec3 pos) {
    return vec3(round(pos.x), round(pos.y), round(pos.z));
}
uint getBlock(ivec3 coord) {
    // TODO: Add more chunks
    if (coord.x > 63 || coord.x < 0 ||coord.y > 63 || coord.y < 0 || coord.z > 63 || coord.z < 0) {
        return 2;
    }

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
    
    float d = rayMarch(rayOrigin, rayDirection);

    vec3 p = rayOrigin + rayDirection * d;
    float dif = getLight(p);
    col = vec3(dif);


    // Positive X to the right
    // Positive Y up
    // Positive Z forward
    // Plane-Assisted Ray Marching
    uint currentBlock = 0;
    ivec3 currentBlockPos = getBlockCoords(rayOrigin);
    while (currentBlock == 0) {
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

        currentBlockPos += distDir;
        currentBlock = getBlock(currentBlockPos);
        rayOrigin += rayDirection * minDist;
    }

    if (currentBlock == 1) {
        col = vec3(0.0f, 1.0f, 0.0f);
    } else {
        col = vec3(0.53f, 0.81f, 0.92f);
    }

    imageStore(screen, pixel_coords, vec4(col, 1.0f));
}