#include "appch.h"
#include "MeshRenderer.h"


namespace Alpha
{
	void MeshRenderer::SetMesh(const Ref<Mesh>& mesh)
	{
		m_Mesh = mesh;

		auto& vertices = mesh->GetVertices();

		m_VertexBuffer.reset(VertexBuffer::Create((float*)&vertices.front(), (uint32_t)vertices.size() * sizeof(float)));
		m_VertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "u_Position" }
			});
		m_VertexBuffer->Bind();

		std::vector<uint32_t> indices = mesh->GetIndices();

		m_IndexBuffer.reset(IndexBuffer::Create((uint32_t*)&indices.front(), (uint32_t)indices.size()));
		m_IndexBuffer->Bind();

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	void MeshRenderer::SetMaterial(const Ref<Material>& material)
	{
		m_Material = material;
	}
}