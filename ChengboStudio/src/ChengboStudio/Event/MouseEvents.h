#include "Event.h"

namespace ChengboStudio 
{
	class CHENGBO_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
		: m_PosX(x), m_PosY(y) {}

		inline float GetPosX() const { return m_PosX; }
		inline float GetPosY() const { return m_PosY; }


		std::string ToString() const override
		{
			std::string str = std::format("MousePositionX: {}, MousePositionY: {}", m_PosX, m_PosY);
			return str;
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(CategoryEvtInput | CategoryMouse)
	private:
		float m_PosX, m_PosY;
	};

	class CHENGBO_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: m_X(x), m_Y(y) {
		}

		inline float GetOffsetX() const { return m_X; }
		inline float GetOffsetY() const { return m_Y; }

		std::string ToString() const override
		{
			std::string str = std::format("ScrollDegreeX: {}, ScrollDegreeY: {}", m_X, m_Y);
			return str;
		}

		EVENT_CLASS_TYPE(Scrolled)
		EVENT_CLASS_CATEGORY(CategoryEvtInput | CategoryMouse)
	private:
		float m_X, m_Y;
	};

	class CHENGBO_API MouseClickEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(ButtonPressed)
		EVENT_CLASS_CATEGORY(CategoryEvtInput | CategoryMouse)

		inline int GetButtonID() const { return m_ID; }

		std::string ToString() const override
		{
			std::string str = std::format("ButtonPressed: {}", m_ID);
			return str;
		}

		MouseClickEvent(int keyid)
			: m_ID(keyid) {
		}
	protected:
		int m_ID;
	};

	class CHENGBO_API MouseReleaseEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(ButtonReleased)
		EVENT_CLASS_CATEGORY(CategoryEvtInput | CategoryMouse)

		inline int GetButtonID() const { return m_ID; }

		std::string ToString() const override
		{
			std::string str = std::format("ButtonReleased: {}", m_ID);
			return str;
		}

		MouseReleaseEvent(int keyid)
			: m_ID(keyid) {
		}
	protected:
		int m_ID;
	};
}