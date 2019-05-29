#version 440 core

uniform sampler2D tex;
uniform vec4 col;

out vec4 color;

in vec2 TexCoords;
in vec3 Normal;

void main()
{
	float up = max(dot(Normal, vec3(0.0, 1.0, 0.0)), 0.7);
	color = texture(tex, TexCoords) * col * up;
}