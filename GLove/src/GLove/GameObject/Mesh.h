#pragma once

#include "Component.h"
#include "Transform.h"

#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

#include "Renderer/Primitives.h"

class Mesh : public Component
{
public:
	Mesh(const Transform& m_Transform);
	~Mesh();
	
	void Load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	virtual void OnRender() override;
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;

	std::vector<Vertex*> m_Vertices;
	std::vector<unsigned int> m_Indices;

	const Transform& m_Transform;
};