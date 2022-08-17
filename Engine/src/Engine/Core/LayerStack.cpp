#include "Engine/pch.h"
#include "Engine/Core/LayerStack.h"

namespace eng
{
	void LayerStack::PushLayer(Layer* pLayer)
	{
		CORE_ASSERT(pLayer != nullptr, "Layer is nullptr!");
		CORE_ASSERT(std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, pLayer) == m_Layers.begin() + m_LayerInsertIndex, "Cannot add the same layer twice!");
		
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, pLayer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* pOverlay)
	{
		CORE_ASSERT(pOverlay != nullptr, "Overlay is nullptr!");
		CORE_ASSERT(std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), pOverlay) == m_Layers.end(), "Cannot add the same overlay twice!");

		m_Layers.emplace_back(pOverlay);
	}

	Layer* LayerStack::PopLayer()
	{
		if (m_LayerInsertIndex == 0)
			return nullptr;

		auto it = m_Layers.begin() + --m_LayerInsertIndex;
		Layer* pLayer = *it;
		m_Layers.erase(it);
		return pLayer;
	}

	Layer* LayerStack::PopOverlay()
	{
		if (m_LayerInsertIndex == m_Layers.size())
			return nullptr;

		auto it = m_Layers.end() - 1;
		Layer* pOverlay = *it;
		m_Layers.erase(it);
		return pOverlay;
	}
}
