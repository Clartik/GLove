#pragma once

#include "GameObject/GameObject.h"
#include "GameObject/Camera/PerspectiveCamera.h"

struct GLFWwindow;

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	void OpenGLInit();
private:
	bool m_Running = true;

	GLFWwindow* m_Window = nullptr;

	GameObject* m_Cube;
	PerspectiveCamera* m_Camera;
};