#pragma once

#include <string>
#include "Alpha/Renderer/Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <unordered_map>
#include "glad/glad.h"

namespace Alpha
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;

		virtual void UploadUniformFloat(const std::string& name, float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) override;

		virtual void UploadUniformInt(const std::string& name, int value) override;

		virtual inline uint32_t GetProgram() const override { return m_RendererID; }

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string ReadFile(const std::string& filepath);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);

	private:
		std::string m_Name = "Shader";
		uint32_t m_RendererID = 0;
	};
}