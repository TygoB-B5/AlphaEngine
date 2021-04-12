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
		std::array<std::string, 6> cubemapTextures =
		{
			"assets/textures/right.jpg",
			"assets/textures/left.jpg",
			"assets/textures/top.jpg",
			"assets/textures/bottom.jpg",
			"assets/textures/front.jpg",
			"assets/textures/back.jpg"
		};

		m_CubemapTexture = Alpha::TextureCubemap::Create(cubemapTextures);


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


		Alpha::Ref<Alpha::VertexBuffer> cubemapVertBuffer;
		cubemapVertBuffer.reset(Alpha::VertexBuffer::Create(vertices, sizeof(vertices)));

		cubemapVertBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" }
			});
		cubemapVertBuffer->Bind();

		Alpha::Ref<Alpha::IndexBuffer> cubematIndexBuffer;
		cubematIndexBuffer.reset(Alpha::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));


		m_CubemapVertexArray.reset(Alpha::VertexArray::Create());
		m_CubemapVertexArray->AddVertexBuffer(cubemapVertBuffer);
		m_CubemapVertexArray->SetIndexBuffer(cubematIndexBuffer);

		m_CubemapShader = Alpha::Shader::Create("assets/shaders/CubemapSky.glshader");
		m_CubemapShader->Bind();


		Alpha::Ref<Alpha::VertexBuffer> cubeVertexBuffer;
		cubeVertexBuffer.reset(Alpha::VertexBuffer::Create(vertices, sizeof(vertices)));

		cubeVertexBuffer->SetLayout(
			{
				{Alpha::ShaderDataType::Float3, "a_Position" }
			});
		cubeVertexBuffer->Bind();

		Alpha::Ref<Alpha::IndexBuffer> cubeIndexBuffer;
		cubeIndexBuffer.reset(Alpha::IndexBuffer::Create(indices, 3 * 6 * 2));

		m_CubeArray.reset(Alpha::VertexArray::Create());
		m_CubeArray->AddVertexBuffer(cubemapVertBuffer);
		m_CubeArray->SetIndexBuffer(cubeIndexBuffer);

		m_TextureShader = Alpha::Shader::Create("assets/shaders/Texture.glshader");
		m_TextureShader->Bind();

		

		std::array<std::string, 6> arr =
		{
			"assets/textures/yes.png",
			"assets/textures/yes.png",
			"assets/textures/yes.png",
			"assets/textures/yes.png",
			"assets/textures/yes.png",
			"assets/textures/yes.png"
		};

		m_TestTex = Alpha::TextureCubemap::Create(arr);
		m_TestTex->Bind();
	}

	virtual void OnUpdate(float deltaTime) override
	{
		Alpha::Renderer::BeginScene(m_Camera);

		Alpha::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Alpha::RenderCommand::Clear();

		Alpha::RenderCommand::EnableDepthMask(false);

		m_CubemapTexture->Bind();
		Alpha::Renderer::Submit(m_CubemapShader, m_CubemapVertexArray, glm::mat4(1.0f));
			
		Alpha::RenderCommand::EnableDepthMask(true);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_TestTex->Bind();
		Alpha::Renderer::Submit(m_TextureShader, m_CubeArray, transform);

		m_Camera.SetRotation({ 0.0f, a, 0.0f });
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::SliderFloat3("Cube Pos", (float*)&pos, -20.0f, 20.0f);
		ImGui::SliderFloat("Rot", &a, -180, 180.0f);
		ImGui::End();
	}
	
	virtual void OnEvent(Alpha::Event& event) override
	{
	}

	private:
		float a = 0;
		glm::vec3 pos = {0.0f, 0.0f, 0.0f};
		Alpha::ShaderLibrary m_ShaderLibrary;

		Alpha::Ref<Alpha::Shader> m_CubemapShader;

		Alpha::Ref<Alpha::Shader> m_TextureShader;

		Alpha::Ref<Alpha::Shader> m_ColorShader;
		Alpha::Ref<Alpha::VertexArray> m_CubeArray;

		Alpha::Ref<Alpha::TextureCubemap> m_TestTex;


		Alpha::Ref<Alpha::VertexArray> m_CubemapVertexArray;
		Alpha::Ref<Alpha::TextureCubemap> m_CubemapTexture;

		Alpha::PerspectiveCamera m_Camera = Alpha::PerspectiveCamera(65.0f, (float)16/9, 0.01f, 100.0f);
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