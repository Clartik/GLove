#include "pch.h"
#include "Window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

static bool s_GLFWInitialized = false;

void GLFWErrorCallback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(const WindowProps& props)
{
	Init(props);
}

Window::~Window()
{
	Shutdown();
}

void Window::OnUpdate()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

void Window::Init(const WindowProps& props)
{
    m_Data.Title =	props.Title;
    m_Data.Width =	props.Width;
    m_Data.Height = props.Height;

    LOG_INFO("Creating New Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        ASSERT(success, "Failed to Initialize GLFW!");
        GLFWerrorfun(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
    ASSERT(m_Window, "Failed to Initalize Window!");

    glfwMakeContextCurrent(m_Window);

    int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(gladStatus, "Failed to Initalize GLAD!");

    glfwSetWindowUserPointer(m_Window, &m_Data);
    //SetVSync();

    // Set GLFW Callbacks
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keyCode);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	});
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
