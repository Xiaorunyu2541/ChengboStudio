#include "pch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ChengboStudio
{
	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		CB_CORE_ASSERT(!s_Instance, "Only a single appliation could exist!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new GuiLayer();
	}

	Application::~Application()
	{

	}
	
	void Application::OnEvent(Event& evt)
	{
		Dispatcher dispatcher(evt);
		dispatcher.Dispatch<EvtWindowClose>(BIND_EVENT_FN(Application::OnWindowClose));

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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_Stack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Active)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto* layer : m_Stack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (auto* layer : m_Stack)
				layer->OnGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(EvtWindowClose& evt)
	{
		m_Active = false;
		return true;
	}
}
