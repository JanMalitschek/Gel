#include "Application.h"
#include "EngineHandler.h"
#include "System.h"
#include "PhysicsEngine.h"

namespace Gel {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		EngineHandler::InitEngine();
		PhysicsEngine::Init();
		OnStart();
		while (!glfwWindowShouldClose(EngineHandler::window)) {
			glfwPollEvents();
			RenderSettings::ClearBuffers();
			System::Run();
			PhysicsEngine::Update(System::GetDeltaTime());
			OnUpdate();
			RenderSettings::postProcessingStack.BeginCapture();
			EngineHandler::UpdateSceneObjects();
			RenderSettings::postProcessingStack.EndCapture();
			RenderSettings::postProcessingStack.Process();
			glfwSwapBuffers(EngineHandler::window);
		}
		OnTerminate();
		glfwTerminate();
	}
}