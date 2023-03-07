#pragma once

#include "Core.h"
#include "Events/event.h"

namespace Pelinjan
{
	class PE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	// to be defined in client
	Application* CreateApplication();

}

