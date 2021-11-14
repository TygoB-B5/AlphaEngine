#include "Sandbox2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
{
}

void Sandbox2D::OnAttach()
{
	m_SquareTexture = Alpha::Texture2D::Create("assets/textures/no.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Fps: %i", (int)Alpha::Time::GetFps());
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));
	ImGui::SliderFloat2("SquarePosition", glm::value_ptr(m_SquarePosition), -10, 10);
	ImGui::SliderFloat2("SquareSize", glm::value_ptr(m_SquareSize), -10, 10);
	ImGui::End();
}

void Sandbox2D::OnUpdate(float deltaTime)
{
	m_OrtographicCameraController.OnUpdate(deltaTime);

	Alpha::Renderer2D::BeginScene(m_OrtographicCameraController.GetCamera());
	Alpha::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	Alpha::RenderCommand::Clear();

	m_SquarePosition.x = sin(Alpha::Time::GetElapsedRealTime() * 2) * 5;
	m_SquarePosition.y = cos(Alpha::Time::GetElapsedRealTime() * 2) * 5;

	Alpha::Renderer2D::DrawQuad({ -1.0f, -3.0f, 0.0f }, { 0.5f, 1.0f }, m_SquareTexture);
	Alpha::Renderer2D::DrawQuad({ 4.0f, 2.0f, 0.0f }, { 0.5f, 1.0f }, m_SquareColor);
	Alpha::Renderer2D::DrawQuad(m_SquarePosition, m_SquareSize, m_SquareTexture);

	Alpha::Renderer2D::EndScene();

}

void Sandbox2D::OnEvent(Alpha::Event& event)
{
	m_OrtographicCameraController.OnEvent(event);
}
