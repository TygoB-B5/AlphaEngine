#include <Alpha.h>

#include "Alpha/Renderer/Shader.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		float verticies[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f
		};

		Alpha::Ref<Alpha::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(Alpha::VertexBuffer::Create(verticies, sizeof(verticies)));
		triangleVertexBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" },
				{Alpha::ShaderDataType::Float4, "a_Color" }
			});

		triangleVertexBuffer->Bind();

		unsigned int indicis[3] = { 0, 1, 2 };

		Alpha::Ref<Alpha::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(Alpha::IndexBuffer::Create(indicis, sizeof(indicis) / sizeof(unsigned int)));
		triangleIndexBuffer->Bind();

		m_VertexArray.reset(Alpha::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);


		float squareVerticies[5 * 4] =
		{
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		Alpha::Ref<Alpha::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Alpha::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));
		squareVertexBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" },
				{Alpha::ShaderDataType::Float2, "a_TexCoord" },
			});

		squareVertexBuffer->Bind();

		unsigned int squareIndicis[6] = { 0, 1, 2, 2, 3, 0 };

		Alpha::Ref<Alpha::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Alpha::IndexBuffer::Create(squareIndicis, sizeof(squareIndicis) / sizeof(unsigned int)));
		squareIndexBuffer->Bind();

		Alpha::Ref<Alpha::Shader> m_SquareShader = m_ShaderLibrary.Load("assets/shaders/Square.glsl");

		m_SquareShader->Bind();

		Alpha::Ref<Alpha::Shader> m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Alpha::Texture2D::Create("assets/textures/no.png");

		m_TextureShader->Bind();
		m_TextureShader->UploadUniformInt("u_Texture", 0);


		m_SquareVertexArray.reset(Alpha::VertexArray::Create());
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
	}

	virtual void OnUpdate(float deltaTime) override
	{
		m_OrtographicCameraController.OnUpdate(deltaTime);

		Alpha::Renderer::BeginScene(m_OrtographicCameraController.GetCamera());

		Alpha::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Alpha::RenderCommand::Clear();

		m_Texture->Bind();
		for (unsigned short x = 0; x < 20; x++)
		{
			for (unsigned short y = 0; y < 20; y++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition + glm::vec3(x * 0.1f + 1.8f, y * 0.1f, 0));
				glm::mat4 transformAndScale = glm::scale(transform, glm::vec3(0.04f, 0.04f, 0.04f));
				m_ShaderLibrary.Get("Square")->UploadUniformFloat3("u_Color", m_SquareColor);
				Alpha::Renderer::Submit(m_ShaderLibrary.Get("Square"), m_SquareVertexArray, transformAndScale);
			}
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition + glm::vec3(0.5f, 0.5f, 0));
		Alpha::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, transform);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
		m_OrtographicCameraController.OnEvent(event);
	}

private:
	Alpha::ShaderLibrary m_ShaderLibrary;
	Alpha::Ref<Alpha::VertexArray> m_VertexArray;
	Alpha::Ref<Alpha::VertexArray> m_SquareVertexArray;

	Alpha::OrtographicCameraController m_OrtographicCameraController = Alpha::OrtographicCameraController((16.0f / 9.0f), true);

	glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.7f };
	glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f };

	Alpha::Ref<Alpha::Texture2D> m_Texture;
};

class Sandbox : public Alpha::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Alpha::Application* Alpha::CreateApplication()
{
	return new Sandbox();
}