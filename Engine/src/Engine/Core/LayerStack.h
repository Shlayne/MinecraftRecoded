#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Layer.h"
#include <vector>

namespace eng
{
	class LayerStack
	{
	public:
		void PushLayer(Layer* pLayer);
		void PushOverlay(Layer* pOverlay);
		Layer* PopLayer();
		Layer* PopOverlay();

		constexpr auto begin() noexcept { return m_Layers.begin(); }
		constexpr auto end() noexcept { return m_Layers.end(); }
		constexpr auto rbegin() noexcept { return m_Layers.rbegin(); }
		constexpr auto rend() noexcept { return m_Layers.rend(); }
		constexpr auto cbegin() const noexcept { return m_Layers.cbegin(); }
		constexpr auto cend() const noexcept { return m_Layers.cend(); }
		constexpr auto crbegin() const noexcept { return m_Layers.crbegin(); }
		constexpr auto crend() const noexcept { return m_Layers.crend(); }
		constexpr auto begin() const noexcept { return m_Layers.begin(); }
		constexpr auto end() const noexcept { return m_Layers.end(); }
		constexpr auto rbegin() const noexcept { return m_Layers.rbegin(); }
		constexpr auto rend() const noexcept { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};
}
