#pragma once

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
};

class Quad
{
public:
	Quad(const glm::vec3& pos, float size)
		: m_Indices{0, 1, 2, 2, 3, 0}
	{
		m_Vertices[0].Position = { pos.x + size, pos.y - size, pos.z };
		m_Vertices[1].Position = { pos.x - size, pos.y - size, pos.z };
		m_Vertices[2].Position = { pos.x - size, pos.y + size, pos.z };
		m_Vertices[3].Position = { pos.x + size, pos.y + size, pos.z };
	}

	inline const Vertex* GetVertices() const { return m_Vertices; }
	inline const unsigned int GetVerticesSize() const { return sizeof(m_Vertices) / sizeof(Vertex); }

	inline const unsigned int* GetIndices() const { return m_Indices; }
	inline const unsigned int GetIndicesSize() const { return sizeof(m_Indices) / sizeof(unsigned int); }
private:
	Vertex m_Vertices[4];
	unsigned int m_Indices[6];
};

class Cube
{
public:
	Cube(const glm::vec3& pos, float size, const glm::vec4& color)
		: m_Indices{ 
			0, 1, 2, 
			2, 3, 0,

			4, 0, 3,
			3, 7, 4,

			5, 4, 7,
			7, 6, 5,

			1, 5, 6,
			6, 2, 1,

			3, 2, 6,
			6, 7, 3,

			4, 5, 1,
			1, 0, 4
		}
	{
		for (int i = 0; i < 8; i++)
		{
			m_Vertices[i].Color = color;
		}

		m_Vertices[0].Position = { pos.x + size, pos.y - size, pos.z + size };
		m_Vertices[1].Position = { pos.x - size, pos.y - size, pos.z + size };
		m_Vertices[2].Position = { pos.x - size, pos.y + size, pos.z + size };
		m_Vertices[3].Position = { pos.x + size, pos.y + size, pos.z + size };

		m_Vertices[4].Position = { pos.x + size, pos.y - size, pos.z - size };
		m_Vertices[5].Position = { pos.x - size, pos.y - size, pos.z - size };
		m_Vertices[6].Position = { pos.x - size, pos.y + size, pos.z - size };
		m_Vertices[7].Position = { pos.x + size, pos.y + size, pos.z - size };
	}

	inline const Vertex* GetVertices() const { return m_Vertices; }
	inline const unsigned int GetVerticesSize() const { return sizeof(m_Vertices) / sizeof(Vertex); }

	inline const unsigned int* GetIndices() const { return m_Indices; }
	inline const unsigned int GetIndicesSize() const { return sizeof(m_Indices) / sizeof(unsigned int); }
private:
	Vertex m_Vertices[8];
	unsigned int m_Indices[36];
};