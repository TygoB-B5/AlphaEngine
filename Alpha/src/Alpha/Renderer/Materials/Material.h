#pragma once
#include "../Shader.h"
#include "Alpha/Core.h"

namespace Alpha
{
	class Material
	{
	public:
		virtual const uint32_t GetMaterialID() const = 0;
		virtual const Ref<Shader> GetShader() const = 0;
		virtual void SetShader(const Ref<Shader>& shader) = 0;
	};

	class StandardMaterial : public Material
	{
	public:
		virtual const uint32_t GetMaterialID() const override { return m_ID; }
		virtual const Ref<Shader> GetShader() const override { return m_Shader; }
		virtual void SetShader(const Ref<Shader>& shader) override { m_Shader = shader; }

	private:
		Ref<Shader> m_Shader;
		uint32_t m_ID = 1;
	};
}