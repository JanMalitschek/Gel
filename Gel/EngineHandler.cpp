#include "EngineHandler.h"
#include "SceneObject.h"

namespace Gel {

	bool EngineHandler::windowIsInFocus = true;
	std::vector<SceneObject*> EngineHandler::sceneObjects = std::vector<SceneObject*>();
	std::vector<SceneObject*> EngineHandler::instancedSceneObjects = std::vector<SceneObject*>();
	GLFWwindow* EngineHandler::window = nullptr;

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

	void EngineHandler::UpdateSceneObjects() {
		for (int i = 0; i < sceneObjects.size(); i++) {
			sceneObjects[i]->Update();
		}
		for (int i = 0; i < instancedSceneObjects.size(); i++) {
			instancedSceneObjects[i]->Update();
		}
	}

}
