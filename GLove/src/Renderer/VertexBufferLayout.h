#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

struct VertexBufferElement
{
	unsigned int Type;
	unsigned int Count;
	bool Normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() {}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	void Push(const std::string& debugName, unsigned int count)
	{
		VertexBufferElement element = { GL_FLOAT, count, GL_FALSE };
		m_Elements.emplace_back(element);
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
};