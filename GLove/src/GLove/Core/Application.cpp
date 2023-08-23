#include "pch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include "GameObject/Mesh.h"

void GLFWErrorCallback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

Application::Application()
{
    Log::Init();
    OpenGLInit();

    m_Cube = new GameObject();
    m_Cube->AddComponent(new Mesh(*m_Cube->GetTransform()));

    m_Camera = new PerspectiveCamera(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
    m_Camera->SetPosition({ 5.0f, 3.0f, -5.0f });

    Cube cube({0.0f, 1.0f, 0.0f, 1.0f});

    m_Cube->GetComponent<Mesh>()->Load(cube.GetVertices(), cube.GetIndices());
    m_Camera->SetLookAt(m_Cube->GetTransform()->GetPosition());
}

Application::~Application()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Run()
{
    while (m_Running)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Cube->OnUpdate();

        m_Cube->OnRender();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::OpenGLInit()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        LOG_ERROR("Failed to Initalize GLFW!");
        return;
    }

    glfwSetErrorCallback(GLFWErrorCallback);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_Window)
    {
        LOG_ERROR("Failed to Initalize the Window!");
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to Initalize GLAD!");
        return;
    }

    LOG_INFO("OpenGL Initialized Sucessfully");
}
