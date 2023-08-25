#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_Model(1.0f)
{
	SetPosition(glm::vec3(0.0f));
	SetScale(glm::vec3(1.0f));
}

Transform::~Transform()
{
}

void Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
	m_Model = glm::translate(m_Model, m_Position);
}

void Transform::SetRotation(float radius, const glm::vec3& axis)
{
	m_Model = glm::rotate(m_Model, glm::radians(radius), axis);
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	m_Model = glm::scale(m_Model, m_Scale);
}

void Transform::SetParent(Transform* parent)
{
	m_Parent = parent;
}
