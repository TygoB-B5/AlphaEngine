#include "appch.h"
#include "Alpha/Physics.h"
#include "PhysicsBody.h"

namespace Alpha
{
	PhysicsBody::PhysicsBody(Ref<GameObject> object)
		: m_ObjectTransform(object->GetComponent<Transform>()), m_Velocity({ 0, 0, 0 })
	{
		Physics::AddPhysicsObject(std::make_shared<PhysicsBody>(*this));
	}
	void PhysicsBody::UpdatePhysics(const float& fixedDeltaTime, const float& deltaTime)
	{
		glm::vec3 acceleration = Physics::GetGravity() * m_Mass / m_Drag;
		m_Velocity += acceleration * m_GravityScale * deltaTime;

		SubmitTransformChange(fixedDeltaTime);
	}
}