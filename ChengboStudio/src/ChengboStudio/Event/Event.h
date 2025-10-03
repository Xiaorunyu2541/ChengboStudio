#pragma once
#include "Core.h"

#include "pch.h"

namespace ChengboStudio {

	enum class EvtType 
	{
		Null = 0,
		Close, Resize, Focus, Unfocus, WindowMoved, // Window
		OnTick, OnUpdate, OnRender, //Application loop
		KeyPressed, KeyReleased, MouseMoved, Scrolled //input
	};

	enum EvtCategory 
	{
		Null = 0,
		CategoryApplication = BIT(0),
		CategoryEvtInput = BIT(1),
		CategoryKeyboard = BIT(2),
		CategoryMouse = BIT(3),
		CategoryMouseButton = BIT(4)
	};
    #define EVENT_CLASS_TYPE(type) static EvtType GetStaticType() { return EvtType::type; }\
    								virtual EvtType GetEventType() const override { return GetStaticType(); }\
    								virtual const char* dbg_GetName() const override { return #type; }
    
    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const { return category; }

	class CHENGBO_API Event
	{
		friend class Dispatch;
	public:
		virtual EvtType GetEventType() const = 0;
		virtual int GetCategory() const = 0;
		virtual const char* dbg_GetName() const = 0;
		virtual std::string ToString() const { return dbg_GetName(); } //probably debug only

		inline virtual bool IsInCategory(EvtCategory category)
		{
			return category & GetCategory();
		}

	protected:
		bool m_Handled;
	};

	class Dispatcher
	{
	public:
		Dispatcher(Event& event)
			: m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}