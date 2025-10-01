#include "Application.h"
#include "Log.h"
#include "Event/AppEvents.h"

namespace ChengboStudio
{
	Application::Application() 
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		EvtWindowResize e(1280, 720);
		CB_TRACE(e.ToString())

		while (true);
	}
}
