#pragma once

#include "Alpha/Core/Window.h"
#include "GLFW/glfw3.h"
#include "Alpha/Renderer/GraphicsContext.h"

namespace Alpha
{
	class  WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* GetNativeWindow() const override { return m_Window; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVsync(bool enabled) override;
		bool IsVsync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown() const;
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title = "Default Window";
			unsigned int Width = 1280, Height = 720;
			bool Vsync = true;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}