#pragma once

#include "Core/InputManager.h"
#include "Core/Application.h"


namespace ChengboStudio {
	class WindowsInput : public InputManager
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		float GetMousePosXImpl() override;
		float GetMousePosYImpl() override;

		std::pair<float, float> GetMousePosImpl() override;
	};
}
