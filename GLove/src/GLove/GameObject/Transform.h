#pragma once

#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::vec3& GetScale() const { return m_Scale; }
	inline const glm::mat4x4& GetModelMatrix() const { return m_Model; }

	void SetPosition(const glm::vec3& pos);
	void SetRotation(float radius, const glm::vec3& axis);
	void SetScale(const glm::vec3& scale);
	void SetParent(Transform* parent);
private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec4 m_Rotation;

	glm::mat4x4 m_Model;

	Transform* m_Parent = nullptr;
};