#include "pch.h"
#include "MainLayer.h"

#include "Renderer/Primitives.h"

#include "glm/glm.hpp"

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
    m_Cube->AddComponent(new Mesh(*m_Cube->GetTransform()));

    Window& window = Application::Get().GetWindow();

    m_Camera = new PerspectiveCamera(45.0f, (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 1000.0f);
    m_Camera->SetPosition({ 5.0f, 3.0f, -5.0f });

    Cube cube({ 0.0f, 1.0f, 0.0f, 1.0f });

    m_Cube->GetComponent<Mesh>()->Load(cube.GetVertices(), cube.GetIndices());
    m_Camera->SetLookAt(m_Cube->GetTransform()->GetPosition());
}

void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(float deltaTime)
{
    m_Cube->OnUpdate(deltaTime);
    m_Cube->GetTransform()->SetRotation(90.0f * deltaTime, { 0.0f, 1.0f, 0.0f });

    m_Cube->OnRender();
}

void MainLayer::OnEvent(Event& e)
{
}
