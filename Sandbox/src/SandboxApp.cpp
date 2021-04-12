 #include <Alpha.h>

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
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
			m_CamPos += forward * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
			m_CamPos += -forward * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
			m_CamPos += -right * deltaTime;

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
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::SliderFloat3("Cube Pos", (float*)&pos, -10.0f, 10.0f);
		ImGui::End();
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
	}

	private:
		float s = 0;
		float g = 0;

		glm::vec3 pos = {-1.0f, 0.0f, 0.0f};
		glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CamPos = { 0.0f, 0.0f, 0.0f };

		Alpha::Ref<Alpha::GameObject> m_GameObject;


		Alpha::Ref<Alpha::Shader> m_PlaneShader;
		Alpha::Ref<Alpha::Texture2D> m_PlaneTex;
		Alpha::Ref<Alpha::VertexArray> m_PlaneArray;


		Alpha::Ref<Alpha::Shader> m_TextureShader;
		Alpha::Ref<Alpha::VertexArray> m_CubeArray;
		Alpha::Ref<Alpha::TextureCubemap> m_TestTex;

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