#version 440 core

uniform sampler2D tex;

out vec4 color;

in vec2 TexCoords;

void main()
{
	color = texture(tex, TexCoords);
}