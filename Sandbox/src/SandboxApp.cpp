 #include <Alpha.h>

class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}


	virtual void OnUpdate() override
	{
		AP_TRACE("ExampleLayer::Update");
	}

	virtual void OnEvent(Alpha::Event& event) override
	{
		AP_TRACE("{0}", event);
	}
};

class Sandbox : public Alpha::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Alpha::ImGuiLayer);
	}

	~Sandbox()
	{

	}
};

Alpha::Application* Alpha::CreateApplication()
{
	return new Sandbox();
}