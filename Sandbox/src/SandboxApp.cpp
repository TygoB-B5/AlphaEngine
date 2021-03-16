#include <Alpha.h>

class Sandbox : public Alpha::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Alpha::Application* Alpha::CreateApplication()
{
	return new Sandbox();
}