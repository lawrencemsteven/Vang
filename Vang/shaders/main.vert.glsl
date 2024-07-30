#version 460 core
	
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_UV;

uniform int u_drawState;

out vec4 v_Color;
out vec2 v_UV;

void main() {
	if (u_drawState == 0) {
		gl_Position = vec4(a_Pos.x, a_Pos.y, 0.0, 1.0);
	} else {
		gl_Position = vec4(a_Pos.x, a_Pos.y, a_Pos.z, 1.0);
	}
	v_Color = a_Color;
	v_UV = a_UV;
}