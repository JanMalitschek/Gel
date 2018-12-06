#pragma once

#include "Core.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Gel {
	class GEL_API Texture {
		Texture(GLuint ID, std::string Name, unsigned int width, unsigned int height);
		Texture();
		int GetWidth();
		int GetHeight();
		GLuint id;
		std::string name;
		unsigned int width, height;
	};
}