#include "pch.h"
#include "Mesh.h"

#include "Camera/Camera.h"

Mesh::Mesh(const Transform& m_Transform)
	: m_Transform(m_Transform)
{
	m_VAO.reset(new VertexArray());
	m_Shader.reset(new Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag"));
}

Mesh::~Mesh()
{
}

void Mesh::Load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_VBO.reset(new VertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex)));

	VertexBufferLayout layout;
	layout.Push("pos", 3);
	layout.Push("color", 4);

	m_VAO->AddBuffer(*m_VBO, layout);

	m_IBO.reset(new IndexBuffer(indices.data(), indices.size()));
}

void Mesh::OnRender()
{
	m_VAO->Bind();
	m_Shader->Bind();

	glm::mat4 mvp = Camera::s_Instance->GetViewProjection() * m_Transform.GetModelMatrix();
	m_Shader->SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);
}
