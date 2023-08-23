#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Transform = new Transform;
	m_Components.emplace_back(m_Transform);
}

GameObject::~GameObject()
{
	for (auto* component : m_Components)
	{
		component->OnDetach();
		delete component;
	}
}

void GameObject::AddComponent(Component* component)
{
	if (dynamic_cast<Transform*>(component))
	{
		LOG_ERROR("Cannot Add Another Transform to a GameObject!");
		return;
	}

	m_Components.emplace_back(component);
	component->OnAttach();
}

void GameObject::RemoveComponent(Component* component)
{
	if (dynamic_cast<Transform*>(component))
	{
		LOG_ERROR("Cannot Delete the Transform of a GameObject!");
		return;
	}

	auto it = std::find(m_Components.begin(), m_Components.end(), component);

	if (it == m_Components.end())
	{
		LOG_WARN("Could Not Remove the Component!");
		return;
	}

	component->OnDetach();
	m_Components.erase(it);
}

void GameObject::OnUpdate()
{
	for (auto& component : m_Components)
		component->OnUpdate();
}

void GameObject::OnRender()
{
	for (auto& component : m_Components)
		component->OnRender();
}
 