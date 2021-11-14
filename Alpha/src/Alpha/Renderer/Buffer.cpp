#include "appch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Alpha/Platform/OpenGL/OpenGLBuffer.h"

namespace Alpha
{
	Ref<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(verticies, size);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* verticies, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(verticies, count);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
