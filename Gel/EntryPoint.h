#pragma once

#include "Application.h"

extern Gel::Application* Gel::CreateApplication();

int main(int argc, char** argv) {
	auto app = Gel::CreateApplication();
	app->Run();
	delete app;
}