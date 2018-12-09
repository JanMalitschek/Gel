#version 440 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
out vec3 Normal;

vec4 VertexJitter(vec4 vertex, int resolution){
	vec4 vert = vertex;
	vert.x = round(vert.x * resolution) / resolution;
	vert.y = round(vert.y * resolution) / resolution;
	vert.z = round(vert.z * resolution) / resolution;
	return vert;
}

void main()
{
	vec4 pos = view * model * vec4(position, 1.0f);
	pos = VertexJitter(pos, 16);
	pos = projection * pos;
    gl_Position = pos;
	TexCoords = texCoords;
	Normal = normal;
}