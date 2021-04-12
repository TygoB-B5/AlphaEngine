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

	class ShaderLibrary
	{
		friend class Shader;
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}