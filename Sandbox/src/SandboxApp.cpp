 #include <Alpha.h>

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
<<<<<<< HEAD
#include <iostream>
=======

>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		unsigned int indices[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

<<<<<<< HEAD
		float vertices[] = {
			// front
			-1.0, -1.0,  1.0,
			 1.0, -1.0,  1.0, 
			 1.0,  1.0,  1.0, 
			-1.0,  1.0,  1.0, 
			// back
			-1.0, -1.0, -1.0,
			 1.0, -1.0, -1.0, 
			 1.0,  1.0, -1.0, 
			-1.0,  1.0, -1.0
		};

		m_TestTex = Alpha::TextureCubemap::Create("assets/textures/wood.jpg");
		m_TestTex->Bind();

		m_TextureShader = Alpha::Shader::Create("assets/shaders/Texture.glshader");
		m_TextureShader->Bind();

		m_GameObject.reset(new Alpha::GameObject("Object"));

		Alpha::Ref<Alpha::Material> material(new Alpha::Material);
		material->SetShader(m_TextureShader);

		Alpha::Ref<Alpha::Mesh> a(new Alpha::Mesh);
		std::vector<float> v(std::begin(vertices), std::end(vertices));
		std::vector<uint32_t> i(std::begin(indices), std::end(indices));
		a->SetVertices(v);
		a->SetIndices(i);

		Alpha::Ref<Alpha::MeshRenderer> renderer(new Alpha::MeshRenderer);
		renderer->SetMesh(a);
		renderer->SetMaterial(material);
		m_GameObject->AddComponent(renderer);
=======
		Alpha::Ref<Alpha::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(Alpha::VertexBuffer::Create(verticies, sizeof(verticies)));
		triangleVertexBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" },
				{Alpha::ShaderDataType::Float4, "a_Color" }
			});	

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

		m_ShaderLibrary.Load("assets/shaders/Texture.glshader");
		auto m_TextureShader = m_ShaderLibrary.Get("Texture");

		m_Texture = Alpha::Texture2D::Create("assets/textures/no.png");
		m_TextureFlushedEmoji = Alpha::Texture2D::Create("assets/textures/yes.png");

		m_TextureShader->UploadUniformInt("u_Texture", 0);

		m_SquareShader = m_ShaderLibrary.Load("assets/shaders/Square.glshader");
		m_SquareVertexArray.reset(Alpha::VertexArray::Create());
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
	}

	virtual void OnUpdate(float deltaTime) override
	{
		Alpha::Renderer::BeginScene(m_Camera);

		Alpha::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Alpha::RenderCommand::Clear();

		m_TestTex->Bind();
		Alpha::Renderer::Submit(m_GameObject);
		m_GameObject->GetComponent<Alpha::Transform>()->SetPosition(pos);
		m_GameObject->GetComponent<Alpha::Transform>()->SetRotation(glm::vec3(g, g, g) * 20.0f);
		m_GameObject->GetComponent<Alpha::Transform>()->SetScale(glm::vec3(1.0f) * abs(sin(g)));

		m_Camera.SetRotation(rot);

		auto& a = m_Camera.GetViewMatrix();
		glm::vec3 right = glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
		glm::vec3 forward = glm::normalize(-glm::vec3(a[0].z, a[1].z, a[2].z));
		glm::vec3 up = glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));


		if (Alpha::Input::IsKeyPressed(AP_KEY_W))
<<<<<<< HEAD
			m_CamPos += forward * deltaTime;

=======
		{
			m_SquarePosition.y += 1 * deltaTime;
		}
		
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
			m_CamPos += -forward * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
			m_CamPos += -right * deltaTime;

<<<<<<< HEAD
		if (Alpha::Input::IsKeyPressed(AP_KEY_A))
			m_CamPos += right * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_Q))
			m_CamPos += up * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_E))
			m_CamPos += -up * deltaTime;

		if (Alpha::Input::IsMouseButtonPressed(0))
			s += 180 * deltaTime;
		if (Alpha::Input::IsMouseButtonPressed(1))
			s += -180 * deltaTime;

		rot.y = s;
		g += deltaTime;
		m_Camera.SetPosition(m_CamPos);
=======
		Alpha::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Alpha::RenderCommand::Clear();
		for (unsigned short x = 0; x < 20; x++)
		{
			for (unsigned short y = 0; y < 20; y++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition + glm::vec3(x * 0.1f + 1.8f, y * 0.1f, 0));
				glm::mat4 transformAndScale = glm::scale(transform, glm::vec3(0.04f, 0.04f, 0.04f));
				m_SquareShader->UploadUniformFloat3("u_Color", m_SquareColor);
				Alpha::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transformAndScale);
			}
		}

		auto m_TextureShader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition + glm::vec3(0.5f, 0.5f, 0));
		Alpha::Renderer::Submit(m_TextureShader, m_SquareVertexArray, transform);

		m_TextureFlushedEmoji->Bind();
		Alpha::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::translate(transform,  glm::vec3(0.5f, 0.5f, 0)));

>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
<<<<<<< HEAD
		ImGui::SliderFloat3("Cube Pos", (float*)&pos, -10.0f, 10.0f);
=======
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
		ImGui::End();
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
	}

	private:
<<<<<<< HEAD
		float s = 0;
		float g = 0;

		glm::vec3 pos = {-1.0f, 0.0f, 0.0f};
		glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CamPos = { 0.0f, 0.0f, 0.0f };

		Alpha::Ref<Alpha::GameObject> m_GameObject;

=======
		Alpha::ShaderLibrary m_ShaderLibrary;
		Alpha::Ref<Alpha::VertexArray> m_VertexArray;

		Alpha::Ref<Alpha::Shader> m_SquareShader;
		Alpha::Ref<Alpha::VertexArray> m_SquareVertexArray;
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c

		Alpha::Ref<Alpha::Shader> m_PlaneShader;
		Alpha::Ref<Alpha::Texture2D> m_PlaneTex;
		Alpha::Ref<Alpha::VertexArray> m_PlaneArray;

<<<<<<< HEAD

		Alpha::Ref<Alpha::Shader> m_TextureShader;
		Alpha::Ref<Alpha::VertexArray> m_CubeArray;
		Alpha::Ref<Alpha::TextureCubemap> m_TestTex;

		Alpha::PerspectiveCamera m_Camera = Alpha::PerspectiveCamera(65.0f, (float)16/9, 0.01f, 100.0f);
=======
		glm::vec3 m_SquarePosition = {0, 0, 0};
		glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.7f };

		Alpha::Ref<Alpha::Texture2D> m_Texture;
		Alpha::Ref<Alpha::Texture2D> m_TextureFlushedEmoji;
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
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