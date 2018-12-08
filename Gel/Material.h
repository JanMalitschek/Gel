#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Shader.h"
#include "DefaultShader.h"

namespace Gel {

	class GEL_API Material {
	public:
		Material();
		virtual void PassValues();
		void SetShader(Shader* shader);
		void UseShader();
		GLuint GetProgram();
		Shader* shader;
	private:
		DefaultShader defaultShader;
	protected:
		void PassTexture(const char* uniformName, GLuint texture, GLenum activeTexture, int activeTextureID);
	};

}

