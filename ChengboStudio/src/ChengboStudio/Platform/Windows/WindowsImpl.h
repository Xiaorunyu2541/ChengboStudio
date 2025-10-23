#pragma once

#include "pch.h"
#include "Core/Window.h"

struct GLFWwindow;

namespace ChengboStudio 
{
	class CHENGBO_API Win32Window : public Window //actually not Win32 but it looks better than WindowsWindow
	{
	public:

		Win32Window(WindowInfo info);

		virtual ~Win32Window();

		void OnUpdate() override;
		void Shutdown();
		
		inline GLFWwindow* GetWindow() { return m_Window; }
		inline uint32_t GetWidth() const override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }
		inline bool GetVSyncState() const override { return m_Data.VSyncState; }

		void SetEventCallBack(const EvtCallbackFn& callback) override { m_Data.callback = callback; }
		void SetVSyncState(bool state);

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowInfo& info);
		virtual void Clean() {};
	private:
		GLFWwindow* m_Window;

		struct BasicData
		{
			std::string WindowTitle;
			uint32_t Width, Height;
			bool VSyncState;
			EvtCallbackFn callback;
		};

		BasicData m_Data;
	};
}