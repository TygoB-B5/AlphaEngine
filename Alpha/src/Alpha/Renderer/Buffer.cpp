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
		case RenderAPI::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RenderAPI::OpenGL: return new OpenGLVertexBuffer(verticies, size);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* verticies, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RenderAPI::OpenGL: return new OpenGLIndexBuffer(verticies, count);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
