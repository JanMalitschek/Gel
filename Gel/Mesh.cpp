#include "Mesh.h"

namespace Gel {

	Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices) {

		this->vertices = vertices;
		this->indices = indices;

		this->SetupMesh();
	}

	void Mesh::SetupMesh() {

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void Mesh::SetVertexPos(unsigned int i, glm::vec3 pos) {
		if (i < this->vertices.size()) {
			this->vertices[i].Position = pos;
		}
		else
			std::cout << "Invalid Vertex Index!" << std::endl;
	}
	void Mesh::SetVertexNormal(unsigned int i, glm::vec3 normal) {
		if (i < this->vertices.size()) {
			this->vertices[i].Normal = normal;
		}
		else
			std::cout << "Invalid Vertex Index!" << std::endl;
	}
	void Mesh::SetVertexUV(unsigned int i, glm::vec2 uv) {
		if (i < this->vertices.size()) {
			this->vertices[i].TexCoords = uv;
		}
		else
			std::cout << "Invalid Vertex Index!" << std::endl;
	}

	void Mesh::UpdateMesh() {
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(Vertex), &this->vertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->indices.size() * sizeof(GLuint), &this->indices[0]);
		glBindVertexArray(0);
	}

	void Mesh::Draw() {
		// Draw mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}