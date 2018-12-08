#pragma once

#include "Core.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace Gel {

	class GEL_API Shader
	{
	public:
		GLuint Program;
		std::string name;
		// Constructor generates the shader on the fly
		Shader();
		Shader(std::string name, const GLchar* vertexPath, const GLchar* fragmentPath);
		// Uses the current shader
		void Use();
		GLuint GetProgram();
	};

}
