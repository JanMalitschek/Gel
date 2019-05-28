#pragma once

#include "Core.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <soil/SOIL.h>

namespace Gel {
	class GEL_API Texture {
	public:
		Texture(GLuint ID, std::string Name, unsigned int width, unsigned int height);
		Texture();
		void Load(const char* path, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT);
		void Create(int width, int height, GLuint filter);
		int GetWidth();
		int GetHeight();
		GLuint id;
		std::string name;
		unsigned int width, height;
	};
}