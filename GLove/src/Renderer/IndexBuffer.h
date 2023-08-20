#pragma once

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	inline unsigned int GetCount() const { return m_Count; }

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};