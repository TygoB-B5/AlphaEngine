#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "Shader.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"

namespace Alpha
{
	class DebugLine
	{
	public:
		DebugLine();

		void DrawLine(const glm::vec3& first, const glm::vec3& second, PerspectiveCamera& camera);

	private:
		void CalculateTransformMatrix(const glm::vec3& first, const glm::vec3& second, const glm::vec3& cameraPos);

	private:
		glm::mat4 m_TransformMatrix;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;

		float m_Vertices[24] = {1.0f, 1.0f, -1.0f,
								 -1.0f, 1.0f, -1.0f,
								 -1.0f, -1.0f, -1.0f,
								1.0f, -1.0f, -1.0f,
								1.0f, 1.0f, 1.0f,
								 -1.0f, 1.0f, 1.0f,
								 -1.0f, -1.0f, 1.0f,
								 1.0f, -1.0f, 1.0f };

		uint32_t m_Indices[36] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3 };
	};
}