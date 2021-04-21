#pragma once
#include "glm/glm.hpp"
#include "Core.h"
#include "Objects/PhysicsBody.h"

namespace Alpha
{
	class Physics
	{
	public:
		Physics();

		static void SetGravity(const glm::vec3& gravity) { s_Gravity = gravity; }
		static const glm::vec3 GetGravity() { return s_Gravity; }

		static void Update(const float& fixedDeltaTime, const float& deltaTime);
		static void AddPhysicsObject(Ref<PhysicsBody> physicsComponent) { m_PhysicsObjects.push_back(physicsComponent); }

	private:
		static glm::vec3 s_Gravity;
		static std::vector<Ref<PhysicsBody>> m_PhysicsObjects;
	};
}