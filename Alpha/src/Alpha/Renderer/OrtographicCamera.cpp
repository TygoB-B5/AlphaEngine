#include "appch.h"
#include "OrtographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
	OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
		:  m_ProjectionMatrix(glm::ortho(left, right, bottom, top, 0.01f, 1000.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrtographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(0.1f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}