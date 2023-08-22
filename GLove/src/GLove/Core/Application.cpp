#include "pch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

void GLFWErrorCallback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

Application::Application()
    : m_Quad({0.0f, 0.0f, 0.0f}, 1.0f), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -10.0f))),
    m_Translation(0.0f, 0.0f, 0.0f), m_Proj(glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f))
{
    Log::Init();
    OpenGLInit();

    Cube cube({ 0.0f, 0.0f, 0.0f }, 1.0f, {0.0f, 1.0f, 0.0f, 1.0f});

    m_VAO.reset(new VertexArray());

    const Vertex* vertices = cube.GetVertices();
    const unsigned int* indices = cube.GetIndices();

    m_VBO.reset(new VertexBuffer(vertices, cube.GetVerticesSize() * sizeof(Vertex)));

    VertexBufferLayout layout;
    layout.Push("pos", 3);
    layout.Push("color", 4);

    m_VAO->AddBuffer(*m_VBO, layout);

    m_IBO.reset(new IndexBuffer(indices, cube.GetIndicesSize()));

    m_Shader.reset(new Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag"));
    m_Shader->Bind();
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

        m_VAO->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

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
