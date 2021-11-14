#include <Alpha.h>
#include "Alpha/Core/EntryPoint.h"

#include "Sandbox2D.h"

class ExampleLayer : public Alpha::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
};

class Sandbox : public Alpha::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Alpha::Application* Alpha::CreateApplication()
{
	return new Sandbox();
}