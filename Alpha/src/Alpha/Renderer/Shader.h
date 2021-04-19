#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

namespace Alpha
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;

		virtual void UploadUniformFloat(const std::string& name, float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) = 0;

		virtual void UploadUniformInt(const std::string& name, int value) = 0;

		virtual inline uint32_t GetProgram() const = 0;

		virtual const std::string& GetName() const = 0;

	public:
		static Ref<Shader> Create(const std::string& name, std::string vertexSrc, std::string fragmentSrc);
		static Ref<Shader> Create(const std::string& filepath);
	};
}