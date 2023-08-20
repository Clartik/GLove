#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Renderer/Primitives.h"
#include "Renderer/Shader.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	GLFWwindow* m_Window = nullptr;

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	
	Square m_Square;
};