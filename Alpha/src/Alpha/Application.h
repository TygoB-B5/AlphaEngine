#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"
#include "Window.h"

namespace Alpha
{
	class ALPHA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in client
	Application* CreateApplication();
}
