#pragma once

#include "Camera.h"

#include "GameObject/Transform.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(GameObject& parent, float fov, float aspectRatio, float nearPlane, float farPlane);
	~PerspectiveCamera();

	virtual const glm::mat4& GetViewProjection() override;
	const glm::mat4& GetView();

	void SetLookAt(const glm::vec3& lookAt);
	void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
private:
	void CalculateViewMatrix();
private:
	const Transform& m_Transform;

	float m_Pitch, m_Yaw;
};