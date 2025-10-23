#pragma once
#include "Core/Layer.h"

#include "Event/AppEvents.h"

namespace ChengboStudio
{
	class CHENGBO_API GuiLayer : public Layer 
	{
	public:
		GuiLayer();
		~GuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}