#include "MinecraftRecoded/pch.h"
#include "WorldLayer.h"
#include <Engine/Core/Application.h>
#include <Engine/Rendering/Renderer.h>
#include "Rendering/BlockRenderer.h"

namespace mcr
{
	WorldLayer::WorldLayer()
	{

	}

	WorldLayer::~WorldLayer()
	{

	}

	void WorldLayer::OnAttach()
	{
		eng::Renderer::SetClearColor({ 0.3f, 0.4f, 1.0f, 1.0f });
		BlockRenderer::Init();
	}

	void WorldLayer::OnDetach()
	{
		BlockRenderer::Shutdown();
	}

	float angle = 0.0f;
	void WorldLayer::OnUpdate(eng::Timestep timestep)
	{
		angle += timestep;
		if (angle >= glm::radians(360.0f))
			angle -= glm::radians(360.0f);
	}

	void WorldLayer::OnRender()
	{
		eng::Renderer::Clear();

		BlockPos blockPos{ glm::s64vec3(0ll, 0ll, 0ll) };
		EntityPos cameraPos{ glm::vec3(3.0f, 2.0f, 5.0f), glm::s64vec3(0ll, 0ll, 0ll) };
		glm::vec3 cameraRotation{ 0.0f, 0.0f, angle };
		BlockRenderer::RenderBlock(blockPos, m_Camera, cameraPos, cameraRotation);
	}

	void WorldLayer::OnEvent(eng::Event& event)
	{
		event.Dispatch(this, &WorldLayer::OnWindowResizeEvent);
		event.Dispatch(this, &WorldLayer::OnWindowFramebufferResizeEvent);
	}

	void WorldLayer::OnWindowResizeEvent(eng::WindowResizeEvent& event)
	{
		m_Camera.Resize(event.GetSize());
	}

	void WorldLayer::OnWindowFramebufferResizeEvent(eng::WindowFramebufferResizeEvent& event)
	{
		eng::Renderer::SetViewport({ 0, 0 }, event.GetSize());
	}
}
