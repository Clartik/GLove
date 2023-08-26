#pragma once

#include "Events/Event.h"

struct GLFWwindow;

struct WindowProps
{
	std::string Title = "App";
	unsigned int Width = 640, Height = 360;
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;
public:
	Window(const WindowProps& props);
	~Window();

	inline GLFWwindow* GetGLFWWindow() const { return m_Window; }

	unsigned int GetWidth() const { return m_Data.Width; }
	unsigned int GetHeight() const { return m_Data.Height; }

	bool IsVSync() const { return m_Data.VSync; }

	void OnUpdate();

	void SetVSync(bool enabled);
	inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
private:
	void Init(const WindowProps& props);
	void Shutdown();
private:
	GLFWwindow* m_Window = nullptr;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	WindowData m_Data;
};