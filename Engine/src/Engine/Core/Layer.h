#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/Event.h"

namespace eng
{
	class Layer
	{
	public:
		virtual ~Layer() = default;
	public:
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& rEvent) {}
	public:
		constexpr bool IsEnabled() const noexcept { return m_Enabled; }
		constexpr void SetEnabled(bool enabled) noexcept { m_Enabled = enabled; }
	private:
		bool m_Enabled = true;
	};
}
