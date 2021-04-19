#pragma once
#include "../Shader.h"
#include "../Texture.h"
#include "Alpha/Core.h"

namespace Alpha
{
	class Material
	{
	public:
		virtual const uint32_t GetMaterialID() const = 0;
		virtual const Ref<Shader> GetShader() const = 0;
		virtual const Ref<Texture2D> GetAlbedo() const = 0;

		virtual void SetShader(const Ref<Shader>& shader) = 0;
		virtual void SetAlbedo(const Ref<Texture2D>& texture) = 0;

		virtual void SetRoughness(const float& value) = 0;
		virtual void SetMetallic(const float& value) = 0;

		virtual void SubmitPropertiesToShader() = 0;
	};

	class StandardMaterial : public Material
	{
	public:
		virtual const uint32_t GetMaterialID() const override { return m_ID; }
		virtual const Ref<Shader> GetShader() const override { return m_Shader; }
		virtual const Ref<Texture2D> GetAlbedo() const override { return m_Albedo; }

		virtual void SetShader(const Ref<Shader>& shader) override { m_Shader = shader; }
		virtual void SetAlbedo(const Ref<Texture2D>& texture) override { m_Albedo = texture; }

		virtual void SetRoughness(const float& value) { m_Roughness = value; }
		virtual void SetMetallic(const float& value) { m_Metallic = value; }

		virtual void SubmitPropertiesToShader() override;
	private:
		float m_Roughness = 0;
		float m_Metallic = 0;
		Ref<Texture2D> m_Albedo;
		Ref<Shader> m_Shader;
		uint32_t m_ID = 1;
	};
}