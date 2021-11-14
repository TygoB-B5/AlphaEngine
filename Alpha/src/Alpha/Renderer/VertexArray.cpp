#include "appch.h"
#include "VertexArray.h"
#include "Alpha/Renderer/Renderer.h"
#include "Alpha/Platform/OpenGL/OpenGLVertexArray.h"

namespace Alpha
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}