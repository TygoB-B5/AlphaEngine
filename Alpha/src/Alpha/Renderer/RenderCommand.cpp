#include "appch.h"
#include "Alpha/Platform/OpenGL/OpenGLRendererAPI.h"
#include "RenderCommand.h"

namespace Alpha
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}