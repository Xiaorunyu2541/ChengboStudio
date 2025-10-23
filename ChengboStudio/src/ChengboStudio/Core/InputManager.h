#pragma once

#include "Core.h"

namespace ChengboStudio 
{
	class CHENGBO_API InputManager 
	{
	public:
		static inline bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static inline float GetMouseX() { return s_Instance->GetMousePosXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMousePosYImpl(); }
		static inline std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static InputManager* s_Instance;
	};
}