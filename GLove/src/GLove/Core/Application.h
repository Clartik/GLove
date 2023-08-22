#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Renderer/Primitives.h"
#include "Renderer/Shader.h"

struct GLFWwindow;

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	void OpenGLInit();
private:
	bool m_Running = true;

	GLFWwindow* m_Window = nullptr;

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;

	glm::mat4 m_View, m_Proj;
	glm::vec3 m_Translation;
	
	Quad m_Quad;
};