#pragma once

#ifdef AP_PLATFORM_WINDOWS
extern Alpha::Application* Alpha::CreateApplication();

int main(int argc, char** argv)
{
	Alpha::Log::Init(); 

	auto app = Alpha::CreateApplication();
	app->Run();
	delete app;
}

#endif