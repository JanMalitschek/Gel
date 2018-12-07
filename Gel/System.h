#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

namespace Gel {
	static class GEL_API System {
	public:
		static void Run();

		static GLfloat GetDeltaTime();
		static GLfloat GetTimeElapsed();
		static void ResetDeltaTime();
	private:
		static GLfloat deltaTime;
		static GLfloat currentFrame;
		static GLfloat lastFrame;
	};
}