#include "appch.h"
#include "WindowsInput.h"
#include "Alpha/Application.h"
#include "GLFW/glfw3.h"

namespace Alpha
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyDownImp(int keycode)
	{
		auto* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindow();

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyHeldImp(int keycode)
	{
		auto* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindow();

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyUpImp(int keycode)
	{
		auto* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindow();

		auto state = glfwGetKey(window, keycode);
		return !(state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImp(int button)
	{
		auto* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImp()
	{
		auto [x, y] = GetMousePositionImp();
		return x;
	}

	float WindowsInput::GetMouseYImp()
	{
		auto[x, y] = GetMousePositionImp();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImp()
	{
		auto* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}
}