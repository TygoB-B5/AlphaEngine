#include "appch.h"
#include "Application.h"

#include <Alpha/Events/KeyEvent.h>

namespace Alpha
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		KeyPressedEvent e(2, 255);

		while (true);
	}
}
