#pragma once

#include "Component.h"

#include <glm/gtx/quaternion.hpp>

class Transform : public Component
{
public:
	Transform(GameObject& parent);
	~Transform();

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::quat& GetRotation() const { return m_Rotation; }
	inline const glm::vec3& GetEulerAngles() const { return glm::eulerAngles(m_Rotation); }
	inline const glm::vec3& GetSize() const { return m_Size; }
	inline const glm::mat4x4& GetModelMatrix() const { return m_Model; }


	inline const glm::vec3& GetForward() const { return m_Forward; }
	inline const glm::vec3& GetRight() const { return m_Right; }
	inline const glm::vec3& GetUp() const { return m_Up; } 

	void SetPosition(const glm::vec3& pos);
	void SetRotation(const glm::vec3& eulerAngles);
	void SetRotation(const glm::quat& quaternion);
	void SetSize(const glm::vec3& size);
	void SetParent(Transform* parent);
private:
	void CalculateVectors();
private:
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Size;

	glm::vec3 m_Forward = { 0.0f, 0.0f, 1.0f };
	glm::vec3 m_Right = { 1.0f, 0.0f, 0.0f };
	glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };

	glm::mat4 m_Model;

	Transform* m_Parent = nullptr;
};