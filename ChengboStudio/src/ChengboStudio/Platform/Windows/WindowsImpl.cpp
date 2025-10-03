#include "pch.h"
#include "WindowsImpl.h"

namespace ChengboStudio 
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowInfo& info)
	{
		return new Win32Window(info);
	}

	Win32Window::Win32Window(WindowInfo info)
	{
		Win32Window::Init(info);
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Win32Window::Init(const WindowInfo& info)
	{
		m_Data.Width = info.m_Width;
		m_Data.Height = info.m_Height;
		m_Data.WindowTitle = info.m_WindowTitle;

		CB_CORE_INFO("Window Initialized: {2}, Resolution: {0} x {1}", info.m_Width, info.m_Height, info.m_WindowTitle);

		if (!s_GLFWInitialized)
		{
			int state = glfwInit();
			CB_CORE_ASSERT(state, "Unable to initialize glfw!");
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.WindowTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSyncState(true);
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Win32Window::SetVSyncState(bool state)
	{
		if (state)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSyncState = state;
	}
}