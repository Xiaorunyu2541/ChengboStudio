#pragma once

#include "InputManager.h"
#include "Application.h"


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
