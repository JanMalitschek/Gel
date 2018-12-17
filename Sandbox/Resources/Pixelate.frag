#version 440 core

uniform sampler2D Gel_ScreenTexture;

out vec4 color;

in vec2 TexCoords;

void main()
{
	vec2 tempCords = TexCoords;
	tempCords.x = floor(tempCords.x * 64) / 64;
	tempCords.y = floor(tempCords.y * 64) / 64;
	vec4 screenColor = texture(Gel_ScreenTexture, tempCords);
	color = vec4(1 - screenColor.x, 1 - screenColor.y, 1 - screenColor.z, 1.0);
}