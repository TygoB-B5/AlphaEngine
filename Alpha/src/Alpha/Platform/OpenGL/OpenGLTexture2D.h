#pragma once
#include <string>
#include "Alpha/Renderer/Texture.h"

namespace Alpha
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override{ return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_FilePath;
		uint32_t m_RendererID;
	};
}