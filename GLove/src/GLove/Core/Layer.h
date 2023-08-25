#pragma once

#include "Core.h"
#include "Events/Event.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer")
		: m_DebugName(name) { }
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnEvent(Event& e) {}

	inline const std::string& GetName() const { return m_DebugName; }
private:
	std::string m_DebugName;
};