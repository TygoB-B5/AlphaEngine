 #include <Alpha.h>

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

		std::string vertexSrc = R"(
		#version 330 core
	
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;		
	
		out vec4 v_Color;	

		void main()
		{
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;		
		in vec4 v_Color;

		void main()
		{
			o_Color = v_Color;
		}
	)";

		m_Shader.reset(Alpha::Shader::Create(vertexSrc, fragmentSrc));
		m_Shader->Bind();

		m_VertexArray.reset(Alpha::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);


		float squareVerticies[3 * 4] =
		{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f
		};

		Alpha::Ref<Alpha::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Alpha::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));
		squareVertexBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" },
			});

		squareVertexBuffer->Bind();

		unsigned int squareIndicis[6] = { 0, 1, 2, 2, 3, 0 };

		Alpha::Ref<Alpha::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Alpha::IndexBuffer::Create(squareIndicis, sizeof(squareIndicis) / sizeof(unsigned int)));
		squareIndexBuffer->Bind();

		std::string squareVertexSrc = R"(
		#version 330 core
	
		layout(location = 0) in vec3 a_Position;
	
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;		

		void main()
		{
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

		std::string squareFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;

		uniform vec3 u_Color;	
		
		void main()
		{
			o_Color = vec4(u_Color, 1.0);
		}
	)";

		m_SquareShader.reset(Alpha::Shader::Create(squareVertexSrc, squareFragmentSrc));
		m_SquareShader->Bind();

		m_SquareVertexArray.reset(Alpha::VertexArray::Create());
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
	}
	virtual void OnUpdate(float deltaTime) override
	{

		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
		{
			m_SquarePosition.x += 1 * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_A))
		{
			m_SquarePosition.x -= 1 * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_W))
		{
			m_SquarePosition.y += 1 * deltaTime;
		}

		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
		{
			m_SquarePosition.y -= 1 * deltaTime;
		}

		Alpha::Renderer::BeginScene(m_Camera);

		Alpha::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Alpha::RenderCommand::Clear();

		m_SquareShader->UploadUniformFloat3("u_Color", m_SquareColor);

		for (unsigned short x = 0; x < 20; x++)
		{
			for (unsigned short y = 0; y < 20; y++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition + glm::vec3(x * 0.1f, y * 0.1f, 0));
				glm::mat4 transformAndScale = glm::scale(transform, glm::vec3(0.04f, 0.04f, 0.04f));

				Alpha::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transformAndScale);
			}
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	virtual void OnEvent(Alpha::Event& event) override
	{

	}

	private:
		float a = 0;
		Alpha::Ref<Alpha::Shader> m_Shader;
		Alpha::Ref<Alpha::VertexArray> m_VertexArray;

		Alpha::Ref<Alpha::Shader> m_SquareShader;
		Alpha::Ref<Alpha::VertexArray> m_SquareVertexArray;

		Alpha::OrtographicCamera m_Camera = Alpha::OrtographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		glm::vec3 m_SquarePosition = {0, 0, 0};
		glm::vec3 m_SquareColor = { 0.4f, 0.2f, 0.8f };
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