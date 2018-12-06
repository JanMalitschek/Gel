#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <soil/SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

namespace Gel {

	struct GEL_API Vertex {
	public:
		Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv) {
			this->Position = pos;
			this->Normal = normal;
			this->TexCoords = uv;
		}
		Vertex() {}
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class GEL_API Mesh {
	public:
		vector<Vertex> vertices;
		vector<GLuint> indices;
		Mesh(vector<Vertex> vertices, vector<GLuint> indices);
		void Draw();
		void UpdateMesh();
		void SetVertexPos(unsigned int i, glm::vec3 pos);
		void SetVertexNormal(unsigned int i, glm::vec3 normal);
		void SetVertexUV(unsigned int i, glm::vec2 uv);

	private:
		GLuint VAO, VBO, EBO;
		void SetupMesh();
	};
}
