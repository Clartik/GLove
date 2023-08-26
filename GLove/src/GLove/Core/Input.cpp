#include "pch.h"
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

bool Input::GetKey(int keycode)
{
	GLFWwindow* window = Application::Get().GetWindow().GetGLFWWindow();
	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::GetMouseButton(int button)
{
	GLFWwindow* window = Application::Get().GetWindow().GetGLFWWindow();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
	GLFWwindow* window = Application::Get().GetWindow().GetGLFWWindow();

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return glm::vec2(x, y);
}

float Input::GetMouseX()
{
	glm::vec2 mousePos = GetMousePosition();
	return mousePos.x;
}

float Input::GetMouseY()
{
	glm::vec2 mousePos = GetMousePosition();
	return mousePos.y;
}
