#pragma once

#include "Alpha/Core.h"

namespace Alpha
{
	class ALPHA_API Input
	{
	public:
		
		inline static bool IsKeyDown(int keycode) { return s_Instance->IsKeyDownImp(keycode); }
		inline static bool IsKeyHeld(int keycode) { return s_Instance->IsKeyHeldImp(keycode); }
		inline static bool IsKeyUp(int keycode) { return s_Instance->IsKeyUpImp(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImp(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImp(); }
		inline static std::pair<float, float> GetMousePosition() {return s_Instance->GetMousePositionImp(); }

	protected:
		virtual bool IsKeyDownImp(int keycode) = 0;
		virtual bool IsKeyHeldImp(int keycode) = 0;
		virtual bool IsKeyUpImp(int keycode) = 0;
		
		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;
		virtual std::pair<float, float> GetMousePositionImp() = 0;
		
	private:
		static Input* s_Instance;
	};
}