#pragma once

#include "Core.h"
#include <stdio.h>
#include <iostream>

namespace Gel {

	class GEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		//Pure virtual methods for user functionality
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnTerminate() = 0;
	};

	//This has to be defined in the client application!
	Application* CreateApplication();

}