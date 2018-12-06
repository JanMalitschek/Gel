#include "Application.h"
#include "EngineHandler.h"

namespace Gel {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		EngineHandler::InitEngine();
		OnStart();
		while (!glfwWindowShouldClose(EngineHandler::window)) {
			glfwPollEvents();
			OnUpdate();
			glfwSwapBuffers(EngineHandler::window);
		}
		OnTerminate();
		glfwTerminate();
	}
}