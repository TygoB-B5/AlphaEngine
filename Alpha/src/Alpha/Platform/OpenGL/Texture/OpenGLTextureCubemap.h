#pragma once
#include <string>
#include <vector>
#include "Alpha/Renderer/Texture.h"

namespace Alpha
{
	class OpenGLTextureCubemap : public TextureCubemap
	{
	public:
		OpenGLTextureCubemap(const std::array<std::string, 6>& filepaths);
		virtual ~OpenGLTextureCubemap();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::array<std::string, 6> m_FilePaths;
		uint32_t m_RendererID;
	};
}