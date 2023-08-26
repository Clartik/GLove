#pragma once

#include "Component.h"

class Light : public Component
{
public:
	Light(GameObject& go);
	~Light();

	void SetIntensity(float intensity);
	void SetColor(const glm::vec4& color);

	virtual void OnRender() override;
private:
	glm::vec4 m_Color;
	float m_Intensity;
};