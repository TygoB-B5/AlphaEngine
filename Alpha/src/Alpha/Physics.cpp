#include "appch.h"
#include "Physics.h"

namespace Alpha
{
	Physics* Physics::s_Instance = new Physics();

	void Physics::Update(const float& fixedDeltaTime)
	{
		s_Instance->UpdatePhysicsImpl(fixedDeltaTime);
	}

	void Physics::AddPhysicsObject(Ref<PhysicsBody> physicsComponent)
	{
		s_Instance->m_PhysicsObjects.push_back(physicsComponent);
	}

	void Physics::UpdatePhysicsImpl(const float& fixedDeltaTime)
	{
		for (auto& object : m_PhysicsObjects)
			object->UpdatePhysics(fixedDeltaTime);
	}
}