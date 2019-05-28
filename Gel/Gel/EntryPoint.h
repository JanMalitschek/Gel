#pragma once

#include "Application.h"

extern Gel::Application* Gel::CreateApplication();

int main(int argc, char** argv) {
	Gel::EngineHandler::InitEngine();
	auto app = Gel::CreateApplication();
	app->Run();
	delete app;
}