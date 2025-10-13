#include "pch.h"
#include "Application.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace ChengboStudio
{
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}
	
	void Application::OnEvent(Event& evt)
	{
		Dispatcher dispatcher(evt);
		dispatcher.Dispatch<EvtWindowClose>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		CB_CORE_INFO("{0}", evt.ToString());

		for (auto it = m_Stack.end(); it != m_Stack.begin(); )
		{
			(*--it)->OnEvent(evt);
			if (evt.GetHandleState())
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Stack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_Stack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Active)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();

			for (auto layer : m_Stack)
				layer->OnUpdate();
		}
	}

	bool Application::OnWindowClose(EvtWindowClose& evt)
	{
		m_Active = false;
		return true;
	}
}
