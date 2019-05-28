#pragma once
#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Gel {

	class GEL_API Renderbuffer
	{
	public:
		Renderbuffer();
		Renderbuffer(int width, int height);
		~Renderbuffer();
		GLuint RBO;
	};

}