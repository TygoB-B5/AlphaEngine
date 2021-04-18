#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

namespace Alpha
{
	class DirectionalLight
	{
	public:
		DirectionalLight(const glm::vec3& direction = glm::vec3(-0.3f, -1.0f, -0.5f), const glm::vec3& color = glm::vec3(1.0f, 1.0f, 0.8f),
			float intensity = 1.5f, const glm::vec3& ambientColor = glm::vec3(0.4f, 0.5f, 1.0f), float ambientIntensity = 0.1f)
			: m_Color(color), m_Direction(direction), m_Intensity(intensity), m_AmbientColor(ambientColor), m_AmbientIntensity(ambientIntensity)
		{}

		void SetIntensity(float intensity) {
			if (intensity < 0)
				intensity = 0;
			m_Intensity = intensity;}

		void SetAmbientIntensity(float intensity) {
			if (intensity < 0)
				intensity = 0;
			m_AmbientIntensity = intensity;
		}

		void SetAmbientColor(const glm::vec3& color) { m_AmbientColor = color; }
		void SetColor(const glm::vec3& color) { m_Color = color; }
		void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

		const float GetIntensity() const { return m_Intensity; }
		const float GetAmbientIntensity() const { return m_AmbientIntensity; }
		const glm::vec3 GetAmbientColor() const { return m_AmbientColor; }
		const glm::vec3 GetColor() const { return m_Color; }
		const glm::vec3 GetDirection() const { return m_Direction; }

	private:
		float m_Intensity;
		float m_AmbientIntensity;
		glm::vec3 m_Color;
		glm::vec3 m_Direction;
		glm::vec3 m_AmbientColor;
	};
}