#pragma once

#include "GameObject/Component.h"

class Camera : public Component
{
public:
	virtual const glm::mat4& GetViewProjection() { return m_ViewProj; }
protected:
	Camera(GameObject& parent);
	virtual ~Camera();
public:
	static Camera* s_Instance;
protected:
	glm::mat4 m_Proj, m_View, m_ViewProj;

	using Component::m_Parent;
;};