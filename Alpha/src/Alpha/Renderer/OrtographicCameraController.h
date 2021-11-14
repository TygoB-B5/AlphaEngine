#pragma once

#include "Alpha/Renderer/OrtographicCamera.h"

#include "glm/glm.hpp"
#include "Alpha/Core/Time.h"

#include "Alpha/Events/ApplicationEvent.h"
#include "Alpha/Events/MouseEvent.h"

namespace Alpha
{
	class OrtographicCameraController
	{
	public:
		OrtographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);

		OrtographicCamera& GetCamera() { return m_Camera; }
		const OrtographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_Rotation;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrtographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_ZoomSpeed = 0.25f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

}