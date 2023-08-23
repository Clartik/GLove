#include "pch.h"
#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

Camera::Camera()
	: m_Proj(0.0f), m_View(0.0f), m_ViewProj(0.0f)
{
}

Camera::~Camera()
{
}
