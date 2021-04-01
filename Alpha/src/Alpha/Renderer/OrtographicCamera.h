#pragma once

#include "glm/glm.hpp"

namespace Alpha
{
	class OrtographicCamera
	{
	public:
		OrtographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(const float& rotation) { m_ZRotation = rotation; RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() { return m_Position; }
		float GetRotation() { return m_ZRotation; }

		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_ZRotation = 0.0f;
	};
}