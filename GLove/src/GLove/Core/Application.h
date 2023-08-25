#pragma once

#include "Window.h"
#include "LayerStack.h"

#include "Events/ApplicationEvent.h"

class Application
{
public:
	Application(const WindowProps& props);
	~Application();

	void Run();
	
	inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
	inline void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }

	inline Window& GetWindow() { return *m_Window; }
	inline static Application& Get() { return *s_Instance; }
private:
	void OnEvent(Event& e);
	bool OnWindowClose(WindowCloseEvent& e);
private:
	bool m_Running = true;
	float m_LastFrameTime = 0.0f;

	Window* m_Window = nullptr;
	LayerStack m_LayerStack;
private:
	static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();