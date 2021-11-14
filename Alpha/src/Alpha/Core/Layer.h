#pragma once

#include "Alpha/Core/Core.h"
#include "Alpha/Events/Event.h"

namespace Alpha
{
	class Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string GetName() const { return m_DebugName; };

	protected:
		std::string m_DebugName;
	};
}