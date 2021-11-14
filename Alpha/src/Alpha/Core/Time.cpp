#include "appch.h"
#include "Time.h"
#include "Alpha/Platform/OpenGL/OpenGLTime.h"
#include "Alpha/Renderer/RendererAPI.h"


namespace Alpha
{
	void Time::Init()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported"); return;
		case RendererAPI::API::OpenGL: s_Time = new OpenGLTime(); return;
		}

		AP_CORE_ASSERT(false, "No Graphics API Found!");
	}
}
