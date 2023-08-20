#include "Application.h"

Application::Application()
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

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
