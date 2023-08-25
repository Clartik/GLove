#include "pch.h"
#include "LayerStack.h"

LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	layer->OnAttach();
	m_Layers.emplace_back(layer);
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

	if (it == m_Layers.end())
	{
		LOG_ERROR("Could Not Pop Layer: {0}", layer->GetName());
		return;
	}

	layer->OnDetach();
	m_Layers.erase(it);
}
