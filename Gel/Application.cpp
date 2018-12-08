#include "Application.h"
#include "EngineHandler.h"
#include "System.h"

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
			RenderSettings::ClearBuffers();
			System::Run();
			OnUpdate();
			glfwSwapBuffers(EngineHandler::window);
		}
		OnTerminate();
		glfwTerminate();
	}
}