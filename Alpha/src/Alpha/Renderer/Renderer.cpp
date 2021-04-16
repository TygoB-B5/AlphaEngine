#include "appch.h"
#include "Renderer.h"
#include "Alpha/Objects/MeshRenderer.h"


namespace Alpha
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::BeginScene(OrtographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform, const DirectionalLight& light, const glm::vec3& camPos)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		
		shader->UploadUniformFloat3("u_CameraPos", camPos);

		shader->UploadUniformFloat3("u_LightColor", light.GetColor());
		shader->UploadUniformFloat3("u_LightAmbientColor", light.GetAmbientColor());
		shader->UploadUniformFloat3("u_LightDirection", light.GetDirection());
		shader->UploadUniformFloat("u_LightAmbientIntensity", light.GetAmbientIntensity());
		shader->UploadUniformFloat("u_LightIntensity", light.GetIntensity());

		vertexArray->Bind();
		vertexArray->GetIndexbuffer()->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}


	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		vertexArray->GetIndexbuffer()->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}