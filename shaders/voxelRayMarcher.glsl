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

float rayMarch(vec3 ro, vec3 rd) {
    float dO = 0.0f;
    
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd*dO;
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

void main() {
    ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
    vec2 uv = (pixel_coords - 0.5*iResolution) / iResolution.y;

    vec3 col = vec3(0);

    vec3 ro = camera.position;
    vec3 rd = normalize(uv.x*camera.right + uv.y*camera.up + (90/camera.fov)*camera.forward);
    
    float d = rayMarch(ro, rd);

    vec3 p = ro + rd * d;
    float dif = getLight(p);
    col = vec3(dif);

    //col *= vec3(1.0f, 0.0f, 0.0f);

    imageStore(screen, pixel_coords, vec4(col, 1.0f));
}