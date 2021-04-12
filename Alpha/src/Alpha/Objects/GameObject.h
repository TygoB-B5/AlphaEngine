#pragma once
#include "Alpha/Core.h"
#include "Component.h"
#include "Transform.h"
#include "GameObjectCount.h"

namespace Alpha
{
	class GameObject
	{
	public:
		GameObject(const std::string& name = "")
		: m_Name(name), m_ObjectID(GameObjectCount::GetNewObjectID())
		{
			if(m_Name == "")
				m_Name = "New Game Object " + std::to_string(m_ObjectID);

			Ref<Transform> a(new Transform); AddComponent(a);
		}

		template<class T>
		const Ref<T> GetComponent()
		{
			for (auto& component : m_Components)
			{
				if (component->GetTypeName() == T::GetStaticName())
					return std::dynamic_pointer_cast<T>(component);
			}

			AP_CORE_WARN("Object does not have component: {0}", T::GetStaticName());
			return nullptr;
		}

		template<class T>
		inline Ref<T> AddComponent(const Ref<T>& component) { m_Components.push_back(component); return component; }

	private:
		std::vector<Ref<Component>> m_Components;
		std::string m_Name;
		std::string m_Tag;
		uint32_t m_ObjectID;
	};
}