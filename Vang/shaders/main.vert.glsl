layout (location = 0) in vec2 a_Pos;
layout (location = 1) in vec2 a_UV;

out vec2 v_UV;

void main() {
	gl_Position = vec4(a_Pos.x, a_Pos.y, 0.0, 1.0);
	v_UV = a_UV;
}