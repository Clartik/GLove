#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	GLFWwindow* m_Window;
};