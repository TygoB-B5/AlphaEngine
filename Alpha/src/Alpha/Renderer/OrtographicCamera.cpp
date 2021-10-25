#include "appch.h"
#include "OrtographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
	OrtographicCamera::OrtographicCamera(float width, float height, float size)
		:  m_ProjectionMatrix(glm::ortho(-width * size, width * size, -height * size, height * size, -0.1f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0)),
		m_Width(width), m_Height(height), m_Size(size)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrtographicCamera::RecalculateProjectionMatrixSize()
	{
		m_ProjectionMatrix = glm::ortho(-m_Width * m_Size, m_Width * m_Size, -m_Height * m_Size, m_Height * m_Size, -0.1f, 1.0f);
		RecalculateViewMatrix();
	}

	void OrtographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(0.1f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_ZRotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}