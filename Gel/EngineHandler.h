#pragma once
#include "Core.h"
#include "RenderSettings.h"
#include "Input.h"
#include <stdio.h>
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Gel {

	static class GEL_API EngineHandler
	{
	public:
		static void InitEngine();
		static void LaunchEngine();
		static void TerminateEngine();
		static void SetWindowTitle(const char title[]);

		static GLFWwindow* window;
	private:
	};

}