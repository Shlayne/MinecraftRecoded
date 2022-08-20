#include "Engine/pch.h"
#include "Engine/Core/LayerStack.h"

namespace eng
{
	void LayerStack::PushLayer(Layer* layer)
	{
		CORE_ASSERT(layer != nullptr, "Layer is nullptr!");
		CORE_ASSERT(std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer) == m_Layers.begin() + m_LayerInsertIndex, "Cannot add the same layer twice!");
		
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		CORE_ASSERT(overlay != nullptr, "Overlay is nullptr!");
		CORE_ASSERT(std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay) == m_Layers.end(), "Cannot add the same overlay twice!");

		m_Layers.emplace_back(overlay);
	}

	Layer* LayerStack::PopLayer()
	{
		if (m_LayerInsertIndex == 0)
			return nullptr;

		auto it = m_Layers.begin() + --m_LayerInsertIndex;
		Layer* layer = *it;
		m_Layers.erase(it);
		return layer;
	}

	Layer* LayerStack::PopOverlay()
	{
		if (m_LayerInsertIndex == m_Layers.size())
			return nullptr;

		auto it = m_Layers.end() - 1;
		Layer* overlay = *it;
		m_Layers.erase(it);
		return overlay;
	}
}
