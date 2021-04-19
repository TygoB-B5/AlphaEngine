#include "appch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Alpha/Platform/OpenGL/OpenGLShader.h"

namespace Alpha
{
	Ref<Shader> Shader::Create(const std::string& name, std::string vertexSrc, std::string fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_unique<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_unique<OpenGLShader>(filepath);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}