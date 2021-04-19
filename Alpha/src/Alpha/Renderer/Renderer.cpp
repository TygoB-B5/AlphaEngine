#include "appch.h"
#include "Renderer.h"

namespace Alpha
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->CameraPosition = camera.GetPosition();
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::SubmitSkybox()
	{
		m_SceneData->Skybox->SetSkyboxPosition(m_SceneData->CameraPosition);

		RenderCommand::EnableDepthMask(false);
		m_SceneData->Skybox->GetCubemap()->Bind(0);
		Alpha::Renderer::Submit(m_SceneData->Skybox->GetVertexArray(), m_SceneData->Skybox->GetShader(), m_SceneData->Skybox->GetTransofrmMatrix());
		RenderCommand::EnableDepthMask(true);
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform)
	{
		auto& shader = material->GetShader();
		material->GetAlbedo()->Bind(1);
		shader->Bind();

		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat3("u_CameraPos", m_SceneData->CameraPosition);
		shader->UploadUniformInt("t_Skybox", 0);
		
		material->SubmitPropertiesToShader();

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