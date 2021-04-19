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

		Alpha::Ref<Alpha::Skybox> m_Skybox = std::make_shared<Alpha::Skybox>(Alpha::Skybox());
		m_Skybox->SetCubemap(Alpha::TextureCubemap::Create({ "assets/textures/right.jpg", "assets/textures/left.jpg",
													  "assets/textures/bottom.jpg", "assets/textures/top.jpg",
													  "assets/textures/front.jpg", "assets/textures/back.jpg" }));
		Alpha::Renderer::SetSkybox(m_Skybox);

		for (unsigned short x = 0; x < 1; x++)
		{
			Alpha::GameObject object;

			object.GetTransform()->SetPosition(glm::vec3(x * 10, 0, 0));
			Alpha::Ref<Alpha::StandardMaterial> material(new Alpha::StandardMaterial);
			material->SetShader(Alpha::Shader::Create("assets/shaders/BasicLit.glshader"));
			material->SetAlbedo(Alpha::Texture2D::Create("assets/textures/dragonlore.png"));
			Alpha::Ref<Alpha::MeshRenderer> renderer(new Alpha::MeshRenderer);
			object.AddComponent(renderer);
			renderer->SetMaterial(material);

			Alpha::Ref<Alpha::Mesh> mesh(new Alpha::Mesh);
			renderer->SetMesh(mesh);
			
			m_GameObjects.push_back(object);

			m_Future.push_back(std::async([mesh, renderer]
				{
				mesh->LoadMeshFromFile("assets/models/dragonlore.obj");
				}));

		Alpha::Renderer::AddLight(std::make_shared<Alpha::DirectionalLight>(Alpha::DirectionalLight()));
		}
	}

	void CalculateStuff(float deltaTime)
	{
		auto& a = m_Camera.GetViewMatrix();
		glm::vec3 right = glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
		glm::vec3 forward = glm::normalize(-glm::vec3(a[0].z, a[1].z, a[2].z));
		glm::vec3 up = glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));

		float speed = 15;
		if (Alpha::Input::IsKeyPressed(AP_KEY_LEFT_SHIFT))
			speed = 30;

		if (Alpha::Input::IsKeyPressed(AP_KEY_W))
			m_CamPos += forward * speed * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_S))
			m_CamPos += -forward * speed * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_D))
			m_CamPos += -right * speed * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_A))
			m_CamPos += right * speed * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_Q))
			m_CamPos += up * speed * deltaTime;

		if (Alpha::Input::IsKeyPressed(AP_KEY_E))
			m_CamPos += -up * speed * deltaTime;

		float newY = Alpha::Input::GetMouseY();
		float newX = Alpha::Input::GetMouseX();

		if (Alpha::Input::IsMouseButtonPressed(1))
		{
			if (newY != oldY)
				rot.x -= (newY - oldY) / 5;
			if (newX != oldX)
				rot.y -= (newX - oldX) / 5;
		}
		oldX = newX;
		oldY = newY;

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(rot);

		b += deltaTime;
		Alpha::Renderer::GetLight(0)->SetDirection(m_DirRot);
	}

	virtual void OnUpdate(const float deltaTime) override
	{
		ExampleLayer::CalculateStuff(deltaTime);

		Alpha::Renderer::BeginScene(m_Camera);

		Alpha::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Alpha::RenderCommand::Clear();

		Alpha::Renderer::SubmitSkybox();

		for (auto& gameObject : m_GameObjects)
		{
			auto& meshR = gameObject.GetComponent<Alpha::MeshRenderer>();
			if (!meshR->IsReadyToInit())
				return;

			//gameObject.GetTransform()->Rotate(glm::vec3(0, 90 * deltaTime, 0));

			auto& pos = gameObject.GetTransform()->GetTransformMatrix();
			Alpha::Renderer::Submit(meshR->GetVertexArray(), meshR->GetMaterial(), pos);
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Value("Fps", Alpha::Time::GetFps());
		ImGui::SliderFloat3("Light ROtation", (float*)&m_DirRot, -1, 1);
		for (auto& gameObject : m_GameObjects)
			ImGui::Text(gameObject.GetName().c_str());
		ImGui::End();
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
		Alpha::EventDispatcher dispatch(event);
		dispatch.Dispatch<Alpha::MouseScrolledEvent>(AP_BIND_EVENT_FN(ExampleLayer::OnMouseScroll));
	}

	bool OnMouseScroll(Alpha::MouseScrolledEvent& e)
	{
		int y = e.GetYOffset();

		auto& a = m_Camera.GetViewMatrix();
		glm::vec3 forward = glm::normalize(-glm::vec3(a[0].z, a[1].z, a[2].z));
		m_CamPos += forward * 2.0f * (float)y;

		return true;
	}

	private:
		float b = 0;

		float oldY = 0;
		float oldX = 0;

		glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CamPos = { 0, 0, 0};
		glm::vec3 m_DirRot = { -0.5f, -1.0f, -0.1f };

		std::vector<Alpha::GameObject> m_GameObjects;

		Alpha::Ref<Alpha::TextureCubemap> m_SkyboxTex;

		Alpha::PerspectiveCamera m_Camera = Alpha::PerspectiveCamera(45.0f, (float)16/9, 0.01f, 1000.0f);

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