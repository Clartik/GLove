#pragma once

#include <glm/glm.hpp>

class Square
{
public:
	Square(float size);
private:
	glm::vec2 m_Vertices[4];
	glm::ivec3 m_Indices[2];
};