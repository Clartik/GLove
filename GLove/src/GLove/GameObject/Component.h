#pragma once

class GameObject;

class Component
{
public:
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
protected:
	Component(GameObject& go)
		: m_Parent(go) { }
protected:
	GameObject& m_Parent;
};