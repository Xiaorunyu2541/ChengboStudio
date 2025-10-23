#include "pch.h"
#include "WindowsImpl.h"

#include "Event/AppEvents.h"
#include "Event/KeyboardEvents.h"
#include "Event/MouseEvents.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ChengboStudio 
{
	static bool s_GLFWInitialized = false;

	static uint8_t s_GLFWWindowCount = 0;

	static uint8_t s_RepeatCount = 0;

	static void ErrorCallBack(int error_code, const char* description)
	{
		CB_CORE_ERROR("Error during initialization: error id [{0}] info: \n{1}", error_code, description);
	}

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
		--s_GLFWWindowCount;
		glfwTerminate();
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
			glfwSetErrorCallback(ErrorCallBack);
			CB_CORE_ASSERT(state, "Unable to initialize glfw!");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.WindowTitle.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;
		glfwMakeContextCurrent(m_Window);
		int state = gladLoadGL(glfwGetProcAddress);
		CB_CORE_ASSERT(state, "failed to load glad")
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSyncState(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);
				info.Width = width;
				info.Height = height;

				EvtWindowResize evt(width, height);
				info.callback(evt);
				
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);
				
				EvtWindowClose evt;
				info.callback(evt);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseClickEvent evt(button);
						info.callback(evt);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseReleaseEvent evt(button);
						info.callback(evt);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent evt((float)xoffset, (float)yoffset);
				info.callback(evt);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);

				MouseMoveEvent evt((float)xpos, (float)ypos);
				info.callback(evt);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				BasicData& info = *(BasicData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressed evt(key, 0);
						info.callback(evt);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleased evt(key);
						info.callback(evt);
						s_RepeatCount = 0;
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressed evt(key, s_RepeatCount);
						info.callback(evt);
						++s_RepeatCount;
						break;
					}
				}
			});
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