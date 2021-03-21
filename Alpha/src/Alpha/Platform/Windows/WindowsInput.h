#pragma once

#include "Alpha/Input.h"

namespace Alpha
{
	class WindowsInput : public Input
	{
	protected:
		
		virtual bool IsKeyDownImp(int keycode) override;
		virtual bool IsKeyHeldImp(int keycode) override;
		virtual bool IsKeyUpImp(int keycode) override;

		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual float GetMouseXImp() override;
		virtual float GetMouseYImp() override;
		virtual std::pair<float, float> GetMousePositionImp() override;
	};
}