#include "appch.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Alpha
{
	void Transform::RecalculateTransformMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_LocalScale);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(1.0f, 0.0f, 1.0f));

		m_TransformMatrix = translate * rotation * scale;
	}
}
