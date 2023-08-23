#pragma once

class Component
{
public:
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnRender() {}
};