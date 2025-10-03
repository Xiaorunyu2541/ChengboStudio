#pragma once
#include "Event.h"
#include "pch.h"

namespace ChengboStudio {
	class Key : public Event
	{
	public:

		EVENT_CLASS_CATEGORY(CategoryEvtInput | CategoryKeyboard)

			inline int GetID() const { return m_ID; }

	protected:
		int m_ID;

		Key(int keyid)
			: m_ID(keyid) {}
	};

	class CHENGBO_API KeyPressed : public Key
	{
	public:
		KeyPressed(int ID, int RepeatCount)
			: Key(ID), m_Repeats(RepeatCount) {}

		std::string ToString() const override
		{
			std::string str = std::format("KeyPressed ID: {}, RepeatTimes: {}", GetID(), m_Repeats);
			return str;
		}

		inline int GetRepeats() const { return m_Repeats; }
		
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_Repeats;
	};

	class CHENGBO_API KeyReleased : public Key
	{
	public:
		KeyReleased(int ID)
			: Key(ID) {
		}

		std::string ToString() const override
		{
			std::string str = std::format("KeyReleased ID: {}", m_ID);
			return str;
		}

		inline int GetID() const { return m_ID; }

		EVENT_CLASS_TYPE(KeyPressed)
	};
}