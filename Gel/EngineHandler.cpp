#include "EngineHandler.h"

namespace Gel {

	bool EngineHandler::windowIsInFocus = true;

	void EngineHandler::windowFocusCallback(GLFWwindow* window, int inFocus) {
		if (inFocus == GLFW_TRUE) {
			windowIsInFocus = true;
		}
		else if (inFocus == GLFW_FALSE) {
			windowIsInFocus = false;
		}
	}


	void EngineHandler::InitEngine() {
		window = RenderSettings::SetupWindow();
		Input::SetupCallBacks(window);
		glfwSetWindowFocusCallback(window, windowFocusCallback);
	}

	void EngineHandler::LaunchEngine() {

	}

	void EngineHandler::TerminateEngine() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void EngineHandler::SetWindowTitle(const char title[]) {
		glfwSetWindowTitle(window, title);
	}

	GLFWwindow* EngineHandler::window = nullptr;
}
