#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Alpha/Core.h"
#include "glm/glm.hpp"
#include "Alpha/Math/Math.h"

namespace Alpha
{
	class PhysicsBody : public Component
	{
	public:
		PhysicsBody(Ref<GameObject> object);

		virtual std::string GetTypeName() const override { return "PhysicsBody"; }
		static std::string GetStaticName() { return "PhysicsBody"; }

	public:
		void SetGravityScale(const float& gravity) { m_GravityScale = Math::Mathf::Clamp(gravity, 0, INFINITY); }
		void SetMass(const float& mass) { m_Mass = Math::Mathf::Clamp(mass, 0.01f, INFINITY); }
		void SetDrag(const float& drag) { m_Drag = Math::Mathf::Clamp(drag, 0.01f, INFINITY); }
		void SetPositionConstraints(int index, const bool& value) { index = Math::Mathi::Clamp(index, 0, 2); m_PositionConstraints[index] = value; }
		void SetRotationConstraints(int index, const bool& value) { index = Math::Mathi::Clamp(index, 0, 2); m_RotationConstraints[index] = value; }
		void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }

		const float GetGravityScale() const { return m_GravityScale; }
		const float GetMass() const { return m_Mass; }
		const float GetDrag() const { return m_Drag; }
		const bool GetPositionConstraints(int index) const { index = Math::Mathi::Clamp(index, 0, 2); return m_PositionConstraints[index]; }
		const bool GetRotationConstraints(int index) const { index = Math::Mathi::Clamp(index, 0, 2); return m_RotationConstraints[index]; }
		const glm::vec3 GetVelocity() const { return m_Velocity; }

		void UpdatePhysics(const float& fixedDeltaTime, const float& deltaTime);

	private:
		inline void SubmitTransformChange(const float& fixedDeltaTime) { m_ObjectTransform->Translate(m_Velocity * fixedDeltaTime); }

	private:
		float m_GravityScale = 1;
		float m_Mass = 1;
		float m_Drag = 1;
		bool m_PositionConstraints[3] = {};
		bool m_RotationConstraints[3] = {};
		glm::vec3 m_Velocity;
		Ref<Transform> m_ObjectTransform;
	};
}