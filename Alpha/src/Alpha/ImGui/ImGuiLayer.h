#pragma once

#include "Alpha/Core/Layer.h"
#include "Alpha/Events/MouseEvent.h"
#include "Alpha/Events/KeyEvent.h"
#include "Alpha/Events/ApplicationEvent.h"

namespace Alpha
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}