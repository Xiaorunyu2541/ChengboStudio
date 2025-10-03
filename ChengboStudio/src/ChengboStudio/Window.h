#pragma once

#include "pch.h"

#include "Log.h"
#include "Core.h"
#include "Event/Event.h"

namespace ChengboStudio 
{
	struct WindowInfo
	{
	public:

		std::string m_WindowTitle;
		uint32_t m_Width;
		uint32_t m_Height;

		WindowInfo(const std::string title = "ChengboStudio",
			uint32_t width = 1280, uint32_t height = 720)
			: m_WindowTitle(title), m_Width(width), m_Height(height) {}
	};

	class CHENGBO_API Window
	{
	public:
		using EvtCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		//universal attributes
		virtual void SetEventCallBack(const EvtCallbackFn& callback) = 0;
		virtual bool GetVSyncState() const = 0;
		virtual void SetVSyncState(bool state) = 0;

		static Window* Create(const WindowInfo& info = WindowInfo());

	};
}
