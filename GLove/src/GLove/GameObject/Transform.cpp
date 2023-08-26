#include "pch.h"
#include "Transform.h"

Transform::Transform(GameObject& parent)
	: Component(parent), m_Model(1.0f)
{
	SetPosition(glm::vec3(0.0f));
	SetSize(glm::vec3(1.0f));
	SetRotation({ 0.0f, 0.0f, 0.0f });
}

Transform::~Transform()
{
}

void Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
	m_Model = glm::translate(m_Model, m_Position);
}

void Transform::SetRotation(const glm::vec3& eulerAngles)
{
	m_Rotation = glm::quat(glm::radians(eulerAngles));
	m_Model *= glm::mat4_cast(m_Rotation);

	CalculateVectors();
}

void Transform::SetRotation(const glm::quat& quaternion)
{
	m_Rotation = quaternion;
	m_Model *= glm::mat4_cast(m_Rotation);

	CalculateVectors();
}

void Transform::SetSize(const glm::vec3& size)
{
	m_Size = size;
	m_Model = glm::scale(m_Model, m_Size);
}

void Transform::SetParent(Transform* parent)
{
	m_Parent = parent;
}

void Transform::CalculateVectors()
{
	m_Forward = glm::rotate(m_Rotation, { 0.0f, 0.0f, -1.0f });
	m_Forward = glm::normalize(m_Forward);

	m_Right = glm::rotate(m_Rotation, { 1.0f, 0.0f, 0.0f });
	m_Right = glm::normalize(m_Right);

	m_Up = glm::rotate(m_Rotation, { 0.0f, 1.0f, 0.0f });
	m_Up = glm::normalize(m_Up);
}
