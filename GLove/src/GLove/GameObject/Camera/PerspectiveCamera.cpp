#include "pch.h"
#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	if (Camera::s_Instance)
		LOG_WARN("Switching Main Camera to Perspective Camera!");

	Camera::s_Instance = this;

	CalculateViewMatrix();
	SetProjection(fov, aspectRatio, nearPlane, farPlane);
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	CalculateViewMatrix();
}

void PerspectiveCamera::SetLookAt(const glm::vec3& lookAt)
{	m_Front = lookAt;
	CalculateViewMatrix();
}

void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_Proj = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	m_ViewProj = m_Proj * m_View;
}

void PerspectiveCamera::CalculateViewMatrix()
{
	m_View = glm::lookAt(m_Position, m_Front, m_Up);
	m_ViewProj = m_Proj * m_View;
}
