#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Alpha
{
	class Transform : public Component
	{
	public:
		Transform()
		{
			RecalculateTransformMatrix();
		}
		virtual std::string GetTypeName() const override { return "Transform"; }
		static std::string GetStaticName() { return "Transform"; }

	public:
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateTransformMatrix(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation;  RecalculateTransformMatrix(); }
		void SetScale(const glm::vec3& scale) { m_LocalScale = scale;  RecalculateTransformMatrix(); }

		const glm::vec3& GetPosition() const { return m_Position;}
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_LocalScale; }

		const glm::mat4& GetTransformMatrix() { return m_TransformMatrix; }


		void Translate(const glm::vec3& translation) { m_Position += translation; RecalculateTransformMatrix(); }
		void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; RecalculateTransformMatrix(); }

	private:
		void RecalculateTransformMatrix();

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_LocalScale = { 1.0f, 1.0f, 1.0f };

		glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
	};
}