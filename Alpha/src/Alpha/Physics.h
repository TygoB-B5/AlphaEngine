#pragma once
#include "glm/glm.hpp"
#include "Core.h"
#include <vector>
#include "Objects/PhysicsBody.h"

namespace Alpha
{
	class Physics
	{
	public:
		const glm::vec3 Gravity = { 0, 9.80f, 0 };
		static void Update(const float& fixedDeltaTime);
		static void AddPhysicsObject(Ref<PhysicsBody> physicsComponent);

		void UpdatePhysicsImpl(const float& fixedDeltaTime);
	private:
		static Physics* s_Instance;
		std::vector<Ref<PhysicsBody>> m_PhysicsObjects;
	};
}