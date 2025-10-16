#pragma once
#include "Layer.h"

#include "imgui.h"
#include "Platform/OpenGL/GuiRenderer.h"

#include "Event/AppEvents.h"

namespace ChengboStudio
{
	class CHENGBO_API GuiLayer : public Layer 
	{
	public:
		GuiLayer();
		~GuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& evt);
	private:
		float m_Time = 0.0f;
	private:
		bool OnWindowResize(EvtWindowResize& evt);
	};
}