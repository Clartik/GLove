#pragma once

#include "Transform.h"

class Entity
{
public:
	Entity();
	~Entity();

	inline const Transform& GetTransform() const { return m_Transform; }
private:
	Transform m_Transform;
	//Mesh m_Mesh;
};