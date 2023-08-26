#include "pch.h"
#include "Light.h"

Light::Light(GameObject& go)
	: Component(go), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Intensity(0.0f)
{
}

Light::~Light()
{
}

void Light::SetIntensity(float intensity)
{
	m_Intensity = intensity;
}

void Light::SetColor(const glm::vec4& color)
{
	m_Color = color;
}

void Light::OnRender()
{
	
}
