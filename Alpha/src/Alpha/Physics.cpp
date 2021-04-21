#include "appch.h"
#include "Physics.h"

namespace Alpha
{
	glm::vec3 Physics::s_Gravity = glm::vec3(0, -9.81f, 0);
	std::vector<Ref<PhysicsBody>> Physics::m_PhysicsObjects;

	Physics::Physics()
	{
	}

	void Physics::Update(const float& fixedDeltaTime, const float& deltaTime)
	{
		for (auto& object : m_PhysicsObjects)
			object->UpdatePhysics(fixedDeltaTime, deltaTime);
	}
}