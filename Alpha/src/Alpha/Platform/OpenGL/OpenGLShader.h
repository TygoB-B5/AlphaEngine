#pragma once

#include "glad/glad.h"
#include <string>
#include "Alpha/Renderer/Shader.h"
#include <unordered_map>
#include "glm/gtc/type_ptr.hpp"


namespace Alpha
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);

		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const  override;

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vector) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vector) override;
		virtual void SetInt(const std::string& name, int value) override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
		void UploadUniformInt(const std::string& name, int value);

		inline uint32_t GetProgram() const override { return m_RendererID; }

	private:
		std::unordered_map<GLenum, std::string> PreProces(const std::string& source);
		std::string ReadFile(const std::string& filepath);
		void Compile(const std::unordered_map<GLenum, std::string>&	 source);
		uint32_t m_RendererID = 0;
		std::string m_Name;
	};
}