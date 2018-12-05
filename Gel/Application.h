#pragma once

#include "Core.h"

namespace Gel {

	class GEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//This has to be defined in the client application!
	Application* CreateApplication();

}