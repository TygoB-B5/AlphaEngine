#include "appch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Alpha/Platform/OpenGL/OpenGLShader.h"

namespace Alpha
{
	Shader* Shader::Create(std::string vertexSrc, std::string fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}