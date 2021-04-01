#pragma once

#include <string>
#include "Alpha/Renderer/Shader.h"
#include "glm/gtc/type_ptr.hpp"

namespace Alpha
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const  override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) override;


		virtual inline uint32_t GetProgram() const override { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
	};
}