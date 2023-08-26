#include "pch.h"
#include "PerspectiveCamera.h"

#include "GameObject/GameObject.h"

PerspectiveCamera::PerspectiveCamera(GameObject& parent, float fov, float aspectRatio, float nearPlane, float farPlane)
	: Camera(parent), m_Transform(*m_Parent.GetTransform())
{
	if (Camera::s_Instance)
		LOG_WARN("Switching Main Camera to Perspective Camera!");

	Camera::s_Instance = this;

	SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	SetProjection(fov, aspectRatio, nearPlane, farPlane);
}

PerspectiveCamera::~PerspectiveCamera()
{
}

const glm::mat4& PerspectiveCamera::GetViewProjection()
{
	m_ViewProj = m_Proj * m_View;

	return m_ViewProj;
}

const glm::mat4& PerspectiveCamera::GetView()
{
	return m_View;
}

void PerspectiveCamera::SetLookAt(const glm::vec3& lookAt)
{
	m_View = glm::lookAt(m_Transform.GetPosition(), lookAt, m_Transform.GetUp());
}

void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_Proj = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

void PerspectiveCamera::CalculateViewMatrix()
{
}
