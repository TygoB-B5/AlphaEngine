#include "appch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Alpha/Platform/OpenGL/OpenGLBuffer.h"

namespace Alpha
{
	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(verticies, size);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indicies, count);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
