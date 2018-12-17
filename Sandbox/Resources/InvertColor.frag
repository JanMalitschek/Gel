#version 440 core

uniform sampler2D Gel_ScreenTexture;

out vec4 color;

in vec2 TexCoords;

void main()
{
	vec4 screenColor = texture(Gel_ScreenTexture, TexCoords);
	color = vec4(1 - screenColor.x, 1 - screenColor.y, 1 - screenColor.z, 1.0);
	//color = vec4(1.0, 0.0, 0.0, 1.0);
}