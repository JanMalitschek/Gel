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

namespace Gel {
	static class GEL_API ShaderContainer {

	public:
		static void LoadShader(Shader* shader);

		static Shader* GetShader(int index);
		static Shader* GetShader(std::string name);

		static void SetActiveShader(GLuint activeShader);
		static GLuint GetActiveShader();

	private:
		static std::vector<Shader*> shaders;
		static GLuint activeShader;
	};
}