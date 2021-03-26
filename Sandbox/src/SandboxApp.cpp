 #include <Alpha.h>

#include "imgui/imgui.h"

class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}


	virtual void OnUpdate() override
	{
		if(Alpha::Input::IsKeyPressed(AP_KEY_SPACE))
			AP_ERROR("hi");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
		
	}
	
	virtual void OnEvent(Alpha::Event& event) override
	{
		if (event.GetEventType() == Alpha::EventType::KeyPressed)
		{
			Alpha::KeyPressedEvent& e = (Alpha::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AP_KEY_SPACE)
				AP_TRACE("hi");
		}

		if (event.GetEventType() == Alpha::EventType::KeyReleased)
		{
			Alpha::KeyPressedEvent& e = (Alpha::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AP_KEY_SPACE)
				AP_WARN("hi");
		}
	}
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