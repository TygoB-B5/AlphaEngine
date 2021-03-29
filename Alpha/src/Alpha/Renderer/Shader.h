#pragma once

#include <string>

namespace Alpha
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual inline uint32_t GetProgram() const = 0;

		static Shader* Create(std::string vertexSrc, std::string fragmentSrc);
	};
}