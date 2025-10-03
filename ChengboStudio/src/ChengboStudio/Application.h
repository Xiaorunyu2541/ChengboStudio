#pragma once

#include "pch.h"

#include "Core.h"
#include "Event/Event.h"

#include "Window.h"

namespace ChengboStudio 
{
	class CHENGBO_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Active = true;
	};

	Application* CreateApplication(); //will be defined in sandbox project
}