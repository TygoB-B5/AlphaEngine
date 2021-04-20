#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Transform.h"
#include "GameObject.h"
#include "Alpha/Core.h"

namespace Alpha
{
	class PhysicsBody : public Component
	{
	public:
		PhysicsBody(Ref<GameObject> object);

		virtual std::string GetTypeName() const override { return "PhysicsBody"; }
		static std::string GetStaticName() { return "PhysicsBody"; }

	public:
		void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
		void UpdatePhysics(const float& fixedDeltaTime) {}
	private:
		float m_GravityScale = 1;
		float m_Mass = 1;
		bool m_PositionConstraints[3] = {};
		bool m_RotationConstraings[3] = {};
		glm::vec3 m_Velocity;
		Ref<Transform> m_ObjectTransform;
	};
}