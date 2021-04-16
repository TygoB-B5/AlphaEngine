#include "appch.h"
#include "PerspectiveCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(fov, aspectRatio, zNear, zFar)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0)), m_Rotation(glm::vec3(0))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(0.1f), m_Position);
		glm::mat4 rotatex = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4 rotatey = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4 rotatez = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse((transform * rotatey) * rotatex * rotatez);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}