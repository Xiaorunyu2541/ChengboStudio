#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Event/AppEvents.h"

#include <GLFW/glfw3.h>

namespace ChengboStudio
{
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Active)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
