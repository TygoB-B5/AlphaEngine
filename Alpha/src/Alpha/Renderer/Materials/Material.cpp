#include "appch.h"
#include "Material.h"
#include "Alpha/Renderer/Renderer.h"

namespace Alpha
{
	void StandardMaterial::SubmitPropertiesToShader()
	{
		auto& light = Renderer::GetLight(0);
		
		AP_CORE_ASSERT(light, "Light at current index does not exist!")

		m_Shader->UploadUniformInt("t_Albedo", 1);
		m_Shader->UploadUniformFloat3("u_Light.color", light->GetColor());
		m_Shader->UploadUniformFloat3("u_Light.ambientColor", light->GetAmbientColor());
		m_Shader->UploadUniformFloat3("u_Light.direction", light->GetDirection());
		m_Shader->UploadUniformFloat("u_Light.ambientIntensity", light->GetAmbientIntensity());
		m_Shader->UploadUniformFloat("u_Light.intensity", light->GetIntensity());
	}
}