#pragma once
#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

namespace Gel {

	class GEL_API PostProcessingStack
	{
	public:
		PostProcessingStack();
		~PostProcessingStack();
		void BeginCapture();
		void EndCapture();
		void Process();
	private:
		float vertices[12] = { 0.0f, 0.0f, 0.0f,
							   1.0f, 0.0f, 0.0f,
							   1.0f, 1.0f, 0.0f,
							   0.0f, 1.0f, 0.0f };
		int indices[6] = {0, 1, 2, 0, 2, 3};
		GLuint VAO, VBO, EBO;
	};

}