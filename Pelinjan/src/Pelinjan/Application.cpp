#include "Application.h"

#include "Pelinjan/Events/ApplicationEvent.h"
#include "Pelinjan/Log.h"

namespace Pelinjan
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		// just for testing the event system
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			PE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryKeyboard))
		{
			PE_TRACE(e);
		}
		// ..
			
		while (true);
	}
}