#include "pch.h"
#include "Core/Application.h"

#include "Layers/MainLayer.h"

class SandboxApp : public Application
{
public:
	SandboxApp(const WindowProps& props)
		: Application(props)
	{
		PushLayer(new MainLayer());
	}

	~SandboxApp()
	{

	}
};

int main()
{
	Application* app = new SandboxApp({ "GLove", 960, 540 });
	app->Run();
	delete app;
}