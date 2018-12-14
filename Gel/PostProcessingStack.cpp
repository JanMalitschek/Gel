#include "PostProcessingStack.h"

namespace Gel {

	PostProcessingStack::PostProcessingStack()
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &this->vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), &this->indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	}


	PostProcessingStack::~PostProcessingStack()
	{
	}

	void PostProcessingStack::BeginCapture()
	{
	}

	void PostProcessingStack::EndCapture()
	{
	}

	void PostProcessingStack::Process()
	{
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6 * sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}