#pragma once

#include "Camera.h"

#include "GameObject/Transform.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);
	~PerspectiveCamera();

	void SetPosition(const glm::vec3& position);
	void SetLookAt(const glm::vec3& lookAt);
	void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
private:
	void CalculateViewMatrix();
private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec3 m_Front = { 0.0f, 0.0f, 1.0f };
	glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
};