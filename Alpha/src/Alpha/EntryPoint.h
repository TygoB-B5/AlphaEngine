#pragma once

#ifdef AP_PLATFORM_WINDOWS
#include <stdio.h>
extern Alpha::Application* Alpha::CreateApplication();

int main(int argc, char** argv)
{
	printf("Alpha Engine has started");
	auto app = Alpha::CreateApplication();
	app->Run();
	delete app;
}

#endif