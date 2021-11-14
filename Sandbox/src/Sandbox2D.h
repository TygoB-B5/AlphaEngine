#pragma once

#include "Alpha.h"

class Sandbox2D : public Alpha::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Alpha::Event& event) override;

private:
	Alpha::OrtographicCameraController m_OrtographicCameraController = Alpha::OrtographicCameraController((16.0f / 9.0f), true);
	Alpha::Ref<Alpha::Shader> m_SquareShader;
	Alpha::Ref<Alpha::VertexArray> m_SquareVertexArray;

	Alpha::Ref<Alpha::Texture2D> m_SquareTexture;

	glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_SquareSize = { 1.0f, 1.0f };
	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.7f, 1.0f };
};

