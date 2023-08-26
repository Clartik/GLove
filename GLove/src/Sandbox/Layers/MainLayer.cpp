#include "pch.h"
#include "MainLayer.h"

#include "Renderer/Primitives.h"

#include "glm/glm.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

MainLayer::MainLayer()
	: Layer("Main Layer")
{
}

MainLayer::~MainLayer()
{
}

void MainLayer::OnAttach()
{
    m_Cube = new GameObject();
    m_Cube->AddComponent(new Mesh(*m_Cube));

    Window& window = Application::Get().GetWindow();

    m_Camera = new GameObject();
    m_Camera->AddComponent(new PerspectiveCamera(*m_Camera, 45.0f, (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 1000.0f));

    PerspectiveCamera& cam = *(PerspectiveCamera*)Camera::s_Instance;
    m_Camera->GetTransform()->SetPosition({ 0.0f, 0.0f, -5.0f });

    Cube cube({ 0.0f, 1.0f, 0.0f, 1.0f });

    m_Cube->GetComponent<Mesh>()->Load(cube.GetVertices(), cube.GetIndices());
    cam.SetLookAt(m_Cube->GetTransform()->GetPosition());
}

void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(float deltaTime)
{
    m_Cube->OnUpdate(deltaTime);
    m_Cube->GetTransform()->SetRotation({ 0.0f, 90.0f * deltaTime, 0.0f });

    m_Cube->OnRender();

    float mouseSpeed = 0.5f;
    float moveSpeed = 30.0f;

    Window& window = Application::Get().GetWindow();

    float horizontal = (window.GetWidth() / 2.0f - Input::GetMouseX()) * deltaTime * mouseSpeed;
    float vertical = (window.GetHeight() / 2.0f - Input::GetMouseY()) * deltaTime * mouseSpeed;

    Transform& cameraTransform = *m_Camera->GetTransform();
    glm::vec3 cameraPos = cameraTransform.GetPosition();
    glm::vec3 eulerAngles = cameraTransform.GetEulerAngles();

    eulerAngles.x += horizontal;
    eulerAngles.y += vertical;

    if (Input::GetKey(KEY_W))
    {
        cameraPos += cameraTransform.GetForward() * moveSpeed * deltaTime;
    }

    if (Input::GetKey(KEY_S))
    {
        cameraPos -= cameraTransform.GetForward() * moveSpeed * deltaTime;
    }

    if (Input::GetKey(KEY_A))
    {
        cameraPos -= cameraTransform.GetRight() * moveSpeed * deltaTime;
    }

    if (Input::GetKey(KEY_D))
    {
        cameraPos += cameraTransform.GetRight() * moveSpeed * deltaTime;
    }

    //LOG_INFO("Camera Position: {0}, {1}, {2}", cameraPos.x, cameraPos.y, cameraPos.z);
    LOG_INFO("Camera Rotation: {0}, {1}, {2}", eulerAngles.x, eulerAngles.y, eulerAngles.z);

    cameraTransform.SetPosition(cameraPos);
    cameraTransform.SetRotation(eulerAngles);

    //glfwSetCursorPos(window.GetGLFWWindow(), window.GetWidth() / 2.0f, window.GetHeight() / 2.0f);
}

void MainLayer::OnEvent(Event& e)
{
}
