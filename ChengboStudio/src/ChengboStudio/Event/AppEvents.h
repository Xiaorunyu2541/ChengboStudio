#pragma once
#include "Event.h"

namespace ChengboStudio 
{
	class CHENGBO_API EvtWindowResize : public Event 
	{
	public:
		EvtWindowResize(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height) {}

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(Resize)
		EVENT_CLASS_CATEGORY(CategoryApplication)

		std::string ToString() const override
		{
			std::string str = std::format("WindowResized Width: {0}, Height: {1}", m_Width, m_Height);
			return str;
		}
	private:
		uint32_t m_Width, m_Height;
	};

	class CHENGBO_API EvtWindowClose : public Event
	{
	public:
		EvtWindowClose() {}

		EVENT_CLASS_TYPE(Close)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class CHENGBO_API EvtOnUpdate : public Event
	{
	public:
		EvtOnUpdate() {}

		EVENT_CLASS_TYPE(OnUpdate)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class CHENGBO_API EvtOnRender : public Event
	{
	public:
		EvtOnRender() {}

		EVENT_CLASS_TYPE(OnRender)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class CHENGBO_API EvtOnTick : public Event
	{
	public:
		EvtOnTick() {}

		EVENT_CLASS_TYPE(OnTick)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};
}