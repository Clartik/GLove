#include "Square.h"

Square::Square(float size)
{
	m_Vertices[0] = {  size,  size };
	m_Vertices[1] = { -size,  size };
	m_Vertices[2] = { -size, -size };
	m_Vertices[3] = {  size, -size };

	m_Indices[0] = { 0, 1, 2 };
	m_Indices[1] = { 2, 3, 0 };
}
