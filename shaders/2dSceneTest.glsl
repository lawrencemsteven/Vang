/* This animation is the material of my first youtube tutorial about creative 
   coding, which is a video in which I try to introduce programmers to GLSL 
   and to the wonderful world of shaders, while also trying to share my recent 
   passion for this community.
                                       Video URL: https://youtu.be/f4s1h2YETNY
*/
#version 460 core
layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D screen;

uniform ivec2 iResolution;
uniform float iTime;

//https://iquilezles.org/articles/palettes/
vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

void main() {
    ivec2 fragCoord = ivec2(gl_GlobalInvocationID.xy);
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

        d = sin(d*8. + iTime)/8.;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        finalColor += col * d;
    }
        
    // fragColor = vec4(finalColor, 1.0);
    imageStore(screen, fragCoord, vec4(finalColor, 1.0f));
}