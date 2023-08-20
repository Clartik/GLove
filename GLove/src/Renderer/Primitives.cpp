#include "pch.h"
#include "Primitives.h"

Square::Square(float size)
	: m_Vertices{size, size, -size, size, -size, -size, size, -size},
	m_Indices{0, 1, 2, 2, 3, 0}
{
}
