#include "appch.h"
#include "Renderer.h"
#include "Alpha/Objects/MeshRenderer.h"

namespace Alpha
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrtographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Submit(const Ref<GameObject>& gameObject)
	{
		auto& meshRenderer = gameObject->GetComponent<MeshRenderer>();
		if (!meshRenderer)
			return;

		auto& shader = meshRenderer->GetMaterial()->GetShader();

		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", gameObject->GetComponent<Transform>()->GetTransformMatrix());

		auto& vertexArray = meshRenderer->GetVertexArray();

		vertexArray->GetIndexbuffer()->Bind();
		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}