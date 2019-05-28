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
		Vertex() {
			this->Position = glm::vec3(0.0f, 0.0f, 0.0f);
			this->Normal = glm::vec3(0.0f, 1.0f, 0.0f);
			this->TexCoords = glm::vec2(0.0f, 0.0f);
		}
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class GEL_API Mesh {
	public:
		vector<Vertex> vertices;
		vector<GLuint> indices;
		Mesh();
		Mesh(unsigned int maxNumVertices, unsigned int maxNumIndices);
		Mesh(vector<Vertex> vertices, vector<GLuint> indices);
		void Draw();
		void UpdateMesh();
		void ReallocateMesh();
		void SetVertexPos(unsigned int i, glm::vec3 pos);
		void SetVertexNormal(unsigned int i, glm::vec3 normal);
		void SetVertexUV(unsigned int i, glm::vec2 uv);
		void SetVertices(vector<Vertex> vertices);
		void SetIndices(vector<GLuint> indices);

	private:
		GLuint VAO, VBO, EBO;
		void SetupMesh();
	};
}
