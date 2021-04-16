#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

namespace Alpha
{
	class DirectionalLight
	{
	public:
		DirectionalLight(const glm::vec3& direction = glm::vec3(0, -1.0f, 0.0f), const glm::vec3& color = glm::vec3(1.0f))
			: m_Color(color), m_Direction(direction)
		{}


		void SetColor(const glm::vec3& color) { m_Color = color; }
		void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

		const glm::vec3 GetColor() const { return m_Color; }
		const glm::vec3 GetDirection() const { return m_Direction; }

	private:
		glm::vec3 m_Color;
		glm::vec3 m_Direction;
	};
}