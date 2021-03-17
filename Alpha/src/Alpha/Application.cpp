#include "appch.h"
#include "Application.h"

#include <Alpha/Events/KeyEvent.h>

#include "GLFW/glfw3.h"

namespace Alpha
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
		m_Window.reset();
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0.6f, 0.7f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}
}
