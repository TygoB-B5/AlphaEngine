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
	
	double m_Etime;

	auto a = std::chrono::steady_clock::now();
	auto b = std::chrono::steady_clock::now();

	void Application::Run()
	{
		while (m_Running)
		{
			a = std::chrono::steady_clock::now();

			m_Etime = std::chrono::duration_cast<std::chrono::milliseconds>(a - b).count();

			double x = sin(m_Etime / 1000) / 2 + 0.5;
			AP_TRACE(x);

			glClearColor(x, x, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}
}
