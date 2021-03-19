#pragma once

#include "Window.h"
#include "Alpha/LayerStack.h"
#include "Core.h"
#include "Events/Event.h"
#include <Alpha/Events/KeyEvent.h>
#include <Alpha/Events/ApplicationEvent.h>

namespace Alpha
{
	class ALPHA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();
}
