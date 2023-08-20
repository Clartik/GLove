#include "pch.h"
#include "Application.h"

#include <glm/gtc/type_ptr.hpp>

Application::Application()
    : m_Square(10)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        LOG_ERROR("Failed to Initalize GLFW!");
        return;
    }

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

    m_VAO.reset(new VertexArray);

    float* vertices = m_Square.GetVertices();
    unsigned int* indices = m_Square.GetIndices();

    VertexBuffer vbo(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push("v_Pos", 2);

    m_VAO->AddBuffer(vbo, layout);

    m_IBO.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));

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
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window))
    {
        /* Render here */
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        m_VAO->Bind();
        m_Shader->Bind();

        glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
