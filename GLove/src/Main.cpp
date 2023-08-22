#include "pch.h"
#include "GLove/Core/Application.h"

int main()
{
	Application* app = new Application;
	app->Run();
	delete app;
}