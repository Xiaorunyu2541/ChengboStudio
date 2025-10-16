#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "pch.h"

namespace ChengboStudio 
{
	InputManager* InputManager::s_Instance = new WindowsInput;

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstace().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	float WindowsInput::GetMousePosXImpl()
	{
		auto[xPos, yPos] = GetMousePosImpl();
		return xPos;
	}

	float WindowsInput::GetMousePosYImpl()
	{
		auto[xPos, yPos] = GetMousePosImpl();
		return yPos;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstace().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::pair<float, float>(xPos, yPos);
	}
}