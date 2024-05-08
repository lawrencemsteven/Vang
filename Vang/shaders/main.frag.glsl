out vec4 FragColor;

uniform sampler2D screen;
in vec2 v_UV;

void main()
{
    FragColor = texture(screen, v_UV);
}