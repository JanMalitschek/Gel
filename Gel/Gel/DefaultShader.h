#pragma once

#include "Core.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace Gel {

	class GEL_API DefaultShader
	{
	public:
		GLuint Program;
		// Constructor generates the shader on the fly
		DefaultShader();
		// Uses the current shader
		void Use();
		GLuint GetProgram();
	};

}