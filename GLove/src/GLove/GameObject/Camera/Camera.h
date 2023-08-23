#pragma once

class Camera
{
public:
	inline const glm::mat4& GetViewProjection() const { return m_ViewProj; }
protected:
	Camera();
	virtual ~Camera();
public:
	static Camera* s_Instance;
protected:
	glm::mat4 m_Proj, m_View, m_ViewProj;
;};