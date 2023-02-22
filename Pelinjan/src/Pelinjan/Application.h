#pragma once

#include "Core.h"

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

