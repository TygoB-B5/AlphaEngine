#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"

namespace Alpha
{
	class ALPHA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}
