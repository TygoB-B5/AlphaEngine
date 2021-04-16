#include "appch.h"
#include "Skybox.h"
#include "Buffer.h"

namespace Alpha
{
	Skybox::Skybox()
		: m_VertexArray(nullptr), m_TransformMatrix(glm::mat4(1.0f)), m_Shader(Shader::Create("assets/shaders/SkyboxShader.glshader"))
	{
		Ref<VertexBuffer> vertexBuffer(VertexBuffer::Create(m_Vertices, 8 * 3 * 4));
		vertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "u_Position"}
			});
		
		Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(m_Indices, 36));
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}
}
