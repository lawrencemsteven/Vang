precision highp float;

#define PI 3.1415926535897932384626433832795

uniform vec2 u_resolution;
uniform vec4 a_position;
uniform float u_time;

float sdCircle(vec2 p, float r, vec2 cpos) {
    return length(p-cpos) - r;
}

float sdBox( in vec2 p, in vec2 b, in vec2 bpos )
{
    vec2 d = abs(p - bpos)-b;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float opUnion( float d1, float d2 )
{
    return min(d1,d2);
}

float opSmoothUnion( float d1, float d2, float k )
{
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h);
}

float opSubtraction( float d1, float d2 )
{
    return max(-d1,d2);
}

float opIntersection( float d1, float d2 )
{
    return max(d1,d2);
}

void main() {
    vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution.xy) / u_resolution.y;

    float radius = sin(mod(u_time / 5.0, 2.0 * PI)) / 4.0 + 0.25;
    float d1 = sdCircle(uv, radius, vec2(0.0));
    float d2 = sdBox(uv, vec2(0.2), vec2(-0.3, 0.3));
    
    // float d = opUnion(d1, d2);
    // float d = opSmoothUnion(d1, d2, 0.1);
    float d = opSubtraction(d1, d2);
    // float d = opIntersection(d1, d2);
    
    float c = (d>0.0) ? 0.5 : 0.25;
    gl_FragColor = vec4(0.2, c, 0.2, 1.0);
}