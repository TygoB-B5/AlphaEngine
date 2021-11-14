#include "appch.h"

#include "OrtographicCameraController.h"

#include "Alpha/Core/Input.h"
#include "Alpha/Core/KeyCodes.h"


namespace Alpha
{
	OrtographicCameraController::OrtographicCameraController(float aspectRatio, bool rotation)
		: m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation), m_AspectRatio(aspectRatio)
	{
	} 

	void OrtographicCameraController::OnUpdate(float deltaTime)
	{
		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * deltaTime;
		}

		if (m_Rotation)
		{
			if (Alpha::Input::IsKeyPressed(AP_KEY_Q))
			{
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
			}

			if (Alpha::Input::IsKeyPressed(AP_KEY_E))
			{
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrtographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(AP_BIND_EVENT_FN(OrtographicCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(AP_BIND_EVENT_FN(OrtographicCameraController::OnWindowResize));
	}

	bool OrtographicCameraController::OnMouseScroll(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * m_ZoomSpeed;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.1f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		
		m_CameraTranslationSpeed = m_ZoomLevel * 1.5f;
		return false;
	}

	bool OrtographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}