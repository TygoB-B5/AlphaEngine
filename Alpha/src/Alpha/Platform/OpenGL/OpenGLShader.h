#pragma once

#include <string>
#include "Alpha/Renderer/Shader.h"

namespace Alpha
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const  override;

		virtual inline uint32_t GetProgram() const override { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
	};
}