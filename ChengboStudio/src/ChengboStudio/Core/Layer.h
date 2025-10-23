#pragma once
#include "Core.h"
#include "Event/Event.h"

namespace ChengboStudio 
{
	class CHENGBO_API Layer
	{
	public:
		Layer(const std::string& name = "Default Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnGuiRender() {}
		virtual void OnEvent(Event& evt) {}

		inline const std::string GetName() { return m_DbgName; }
	protected:
		std::string m_DbgName;
	};
}