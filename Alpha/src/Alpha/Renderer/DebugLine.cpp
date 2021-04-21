#include "appch.h"
#include "DebugLine.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Alpha
{
	DebugLine::DebugLine()
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

		m_Shader = Shader::Create("assets/shaders/GreenUnlit.glshader");
	}

	void DebugLine::DrawLine(const glm::vec3& first, const glm::vec3& second, PerspectiveCamera& camera)
	{
		if (first == second)
			return;

		CalculateTransformMatrix(first, second, camera.GetPosition());
		Renderer::Submit(m_VertexArray, m_Shader, m_TransformMatrix);
	}

	void DebugLine::CalculateTransformMatrix(const glm::vec3& first, const glm::vec3& second, const glm::vec3& cameraPos)
	{
		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, (first + second) * 0.5f);

		glm::vec3 tragetVec = glm::normalize(second - first);
		glm::quat rotQuat = glm::rotation(glm::vec3(0, 1, 0), tragetVec);
		auto rotationMatrix = glm::toMat4(rotQuat);
		transform *= rotationMatrix;

		float size = 0.002f + glm::length((first + second) * 0.5f - cameraPos) * 0.0003f;

		transform = glm::scale(transform, glm::vec3(size, glm::length(second - first) * 0.5f, size));

		m_TransformMatrix = transform;
	}
}
