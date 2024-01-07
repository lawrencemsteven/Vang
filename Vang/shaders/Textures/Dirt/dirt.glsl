precision highp float;

uniform vec2 u_resolution;
uniform vec4 a_position;

float sdCircle(vec2 p, float r, vec2 cpos) {
    return length(p-cpos) - r;
}

void main() {
    vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution.xy) / u_resolution.y;

    //float d = sdCircle(uv, 1., vec2(0.0, 0.0));
    //float c = (d>0.0) ? 1.0 : 0.5;
    //gl_FragColor = vec4(c, 0.0, 0.0, 1.0);

    gl_FragColor = vec4(0.2824, 0.1569, 0.0588, 1.0);
}