#version 460 core

out vec4 FragColor;

uniform int u_drawState;

uniform sampler2D screen;

in vec4 v_Color;
in vec2 v_UV;

const highp float NOISE_GRANULARITY = 1.0/255.0;

highp float random(highp vec2 coords) {
   return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	if (u_drawState == 0) {
		FragColor = texture(screen, v_UV);
	} else {
		//FragColor = v_UV_or_Color;
		FragColor = vec4(v_UV, 0.0, 1.0);

		// Fix Color Banding
		FragColor += mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(gl_FragCoord.xy));
	}

}