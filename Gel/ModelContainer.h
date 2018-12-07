#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "Model.h"

namespace Gel {

	static class GEL_API ModelContainer {

	public:
		static void LoadModel(GLchar* path);
		static void LoadModel(std::string name, GLchar* path);
		static Model GetModel(int index);
		static Model GetModel(std::string name);

	private:
		static vector<Model> modelContainer;
	};
}
