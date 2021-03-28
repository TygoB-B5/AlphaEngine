#pragma once

#include <string>

namespace Alpha
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void UnBind();

		inline uint32_t GetProgram() const { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;

	};
}