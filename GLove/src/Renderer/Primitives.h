#pragma once

class Square
{
public:
	Square(float size);

	inline float* GetVertices() { return m_Vertices; }
	inline unsigned int* GetIndices() { return m_Indices; }
private:
	float m_Vertices[8];
	unsigned int m_Indices[6];
};