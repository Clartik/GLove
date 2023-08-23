#pragma once

#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform* GetTransform() const { return m_Transform; }

	template<typename T>
	T* GetComponent();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void OnUpdate();
	void OnRender();
private:
	Transform* m_Transform = nullptr;

	std::vector<Component*> m_Components;
};

template<typename T>
T* GameObject::GetComponent()
{
	for (Component* component : m_Components)
	{
		T* castedComponent = dynamic_cast<T*>(component);

		if (castedComponent)
			return castedComponent;
	}

	LOG_WARN("Could Not Find the Component!");
	return nullptr;
}
