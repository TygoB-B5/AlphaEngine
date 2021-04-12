#include "appch.h"
#include "Texture.h"
#include "Renderer.h"
<<<<<<< HEAD
#include "Alpha/Platform/OpenGL/Texture/OpenGLTexture2D.h"
#include "Alpha/Platform/OpenGL/Texture/OpenGLTexture3D.h"

#include "Alpha/Platform/OpenGL/Texture/OpenGLTextureCubemap.h"
=======
#include "Alpha/Platform/OpenGL/OpenGLTexture2D.h"
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c

namespace Alpha
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(filepath);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
<<<<<<< HEAD

	Ref<TextureCubemap> TextureCubemap::Create(const std::array<std::string, 6>& filepaths)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTextureCubemap>(filepaths);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<TextureCubemap> TextureCubemap::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTextureCubemap>(filepath);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture3D> Texture3D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: AP_CORE_ASSERT(false, "RenderAPI: \"None\" is not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture3D>(filePath);
		}

		AP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
=======
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
}