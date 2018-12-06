#include "EngineHandler.h"

namespace Gel {

	void EngineHandler::InitEngine() {
		window = RenderSettings::SetupWindow();
		Input::SetupCallBacks(window);
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
