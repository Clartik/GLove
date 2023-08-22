#pragma once

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(const glm::vec3& pos);
private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;
};