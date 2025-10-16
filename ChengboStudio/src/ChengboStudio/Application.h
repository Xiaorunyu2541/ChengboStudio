#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Event/AppEvents.h"
#include "LayerStack.h"


#include "Window.h"

namespace ChengboStudio 
{
	class CHENGBO_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& evt);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetInstace() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(EvtWindowClose& evt);

		std::unique_ptr<Window> m_Window;
		bool m_Active = true;
		LayerStack m_Stack;
		static Application* s_Instance;
	};

	Application* CreateApplication(); //will be defined in sandbox project
}