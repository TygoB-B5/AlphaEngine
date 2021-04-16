 #include <Alpha.h>

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <future>

class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_SkyboxTex = Alpha::TextureCubemap::Create({ "assets/textures/right.jpg", "assets/textures/left.jpg",
													  "assets/textures/top.jpg", "assets/textures/bottom.jpg", 
													  "assets/textures/front.jpg", "assets/textures/back.jpg" });
		
		m_TestTex = Alpha::Texture2D::Create("assets/textures/wood.jpg");

		for (unsigned short x = 0; x < 1; x++)
		{
			Alpha::GameObject object;

			Alpha::Ref<Alpha::Shader> textureShader = Alpha::Shader::Create("assets/shaders/BasicLit.glshader");

			object.GetTransform()->SetPosition(glm::vec3(x, 0, 0) * 3.0f);

			Alpha::Ref<Alpha::StandardMaterial> material(new Alpha::StandardMaterial);
			material->SetShader(textureShader);

			Alpha::Ref<Alpha::MeshRenderer> renderer(new Alpha::MeshRenderer);
			object.AddComponent(renderer);
			renderer->SetMaterial(material);

			Alpha::Ref<Alpha::Mesh> mesh(new Alpha::Mesh);
			renderer->SetMesh(mesh);

			m_GameObjects.push_back(object);

			m_Future.push_back(std::async([mesh, renderer]
				{
					mesh->LoadMeshFromFile("assets/models/sphere.obj");
				}));

		m_Skybox.SetSkyboxFollowPositionReference(&m_CamPos);
		}
	}

	void CalculateStuff(float deltaTime)
	{
		auto& a = m_Camera.GetViewMatrix();
		glm::vec3 right = glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
		glm::vec3 forward = glm::normalize(-glm::vec3(a[0].z, a[1].z, a[2].z));
		glm::vec3 up = glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));

		if (Alpha::Input::IsKeyPressed(AP_KEY_W))
			m_CamPos += forward * 10.0f * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
			m_CamPos += -forward * 10.0f * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
			m_CamPos += -right * 10.0f * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_A))
			m_CamPos += right * 10.0f * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_Q))
			m_CamPos += up * 10.0f * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_E))
			m_CamPos += -up * 10.0f * deltaTime;

		if (Alpha::Input::IsMouseButtonPressed(0))
			s += 180 * deltaTime;
		if (Alpha::Input::IsMouseButtonPressed(1))
			s += -180 * deltaTime;

		rot.y = s;
		g += deltaTime;

		m_Camera.SetPosition(m_CamPos);
		m_Dirlight.SetDirection(glm::vec3(-0.5f, -1.0f, -0.2f));
	}

	virtual void OnUpdate(const float deltaTime) override
	{
		ExampleLayer::CalculateStuff(deltaTime);
		m_Camera.SetRotation(rot);


		Alpha::Renderer::BeginScene(m_Camera);

		Alpha::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Alpha::RenderCommand::Clear();

		Alpha::RenderCommand::EnableDepthMask(false);
		m_SkyboxTex->Bind();
		Alpha::Renderer::Submit(m_Skybox.GetVertexArray(), m_Skybox.GetShader(), m_Skybox.GetTransofrmMatrix());
		Alpha::RenderCommand::EnableDepthMask(true);

		m_TestTex->Bind();
		for (auto& gameObject : m_GameObjects)
		{
			auto& meshR = gameObject.GetComponent<Alpha::MeshRenderer>();
			if (!meshR->IsReadyToInit())
				return;
			auto& vert = meshR->GetVertexArray();
			auto& shad = meshR->GetMaterial()->GetShader();
			auto& pos = gameObject.GetComponent<Alpha::Transform>()->GetTransformMatrix();

			gameObject.GetTransform()->SetRotation(glm::vec3(0, g, 0) * 80.0f);
			gameObject.GetTransform()->SetPosition(m_Pos);

			Alpha::Renderer::Submit(vert, shad, pos, m_Dirlight);
		}

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::SliderFloat3("Cube Pos", (float*)&m_Pos, -10.0f, 10.0f);
		ImGui::Value("Fps", Alpha::Time::GetFps());
		for (auto& gameObject : m_GameObjects)
			ImGui::Text(gameObject.GetName().c_str());
		ImGui::End();
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
	}

	private:
		float s = 0;
		float g = 0;
		int b = 0;

		glm::vec3 m_Pos = {0.0f, 0.0f, 0.0f};
		glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CamPos = { 0.0f, 0.0f, 4.5f };

		std::vector<Alpha::GameObject> m_GameObjects;
		Alpha::Ref<Alpha::TextureCubemap> m_SkyboxTex;
		Alpha::Ref<Alpha::Texture2D> m_TestTex;

		Alpha::Skybox m_Skybox;
		Alpha::PerspectiveCamera m_Camera = Alpha::PerspectiveCamera(45.0f, (float)16/9, 0.01f, 1000.0f);
		Alpha::OrtographicCamera m_OrtCamera = Alpha::OrtographicCamera(-1.6f * 100, 1.6f * 100, -0.9f * 100, 0.9f * 100, 0.01f, 1000.0f);

		Alpha::DirectionalLight m_Dirlight = Alpha::DirectionalLight();

		std::vector<std::future<void>> m_Future;
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