#pragma once

#include <Engine/Core/Layer.h>
#include <Engine/Events/WindowEvents.h>
#include "Rendering/Camera.h"

namespace mcr
{
	class WorldLayer : public eng::Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(eng::Timestep timestep) override;
		virtual void OnRender() override;
		virtual void OnEvent(eng::Event& event) override;
	private:
		void OnWindowResizeEvent(eng::WindowResizeEvent& event);
		void OnWindowFramebufferResizeEvent(eng::WindowFramebufferResizeEvent& event);
	private:
		Camera m_Camera;
	};
}
