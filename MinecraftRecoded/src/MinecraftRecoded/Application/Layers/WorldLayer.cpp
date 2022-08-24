#include "MinecraftRecoded/pch.h"
#include "WorldLayer.h"
#include <Engine/Core/Application.h>
#include <Engine/Rendering/Renderer.h>
#include "Modding/ModLoader.h"
#include "Modding/Registry.h"
#include "Rendering/ChunkRenderer.h"

namespace mcr
{
	void WorldLayer::OnAttach()
	{
		ModLoader::Load();
		Registry::Init();

		eng::Renderer::SetClearColor({ 0.3f, 0.4f, 1.0f, 1.0f });
		ChunkRenderer::Init();

		m_Chunk = new Chunk();
	}

	void WorldLayer::OnDetach()
	{
		delete m_Chunk;

		ChunkRenderer::Shutdown();

		Registry::Shutdown();
		ModLoader::Unload();
	}

	EntityPos cameraPos{ glm::vec3(-2.0f, 2.0f, -2.0f), glm::s64vec3(0ll, 1ll, 0ll) };
	glm::vec3 cameraRotation{ glm::radians(-45.0f), glm::radians(-135.0f), 0.0f};

	void WorldLayer::OnUpdate(eng::Timestep timestep)
	{
		auto& Input = eng::Input::Get();

		constexpr float rotationSpeed = 1.0f;
		if (Input.IsKeyPressed(eng::Keycode_Left))
			cameraRotation.y += rotationSpeed * timestep;
		if (Input.IsKeyPressed(eng::Keycode_Right))
			cameraRotation.y -= rotationSpeed * timestep;
		if (Input.IsKeyPressed(eng::Keycode_Up))
			cameraRotation.x += rotationSpeed * timestep;
		if (Input.IsKeyPressed(eng::Keycode_Down))
			cameraRotation.x -= rotationSpeed * timestep;

		constexpr float movementSpeed = 5.0f;
		if (Input.IsKeyPressed(eng::Keycode_D))
		{
			cameraPos.x += movementSpeed * std::cos(cameraRotation.y) * timestep;
			cameraPos.z -= movementSpeed * std::sin(cameraRotation.y) * timestep;
		}
		if (Input.IsKeyPressed(eng::Keycode_A))
		{
			cameraPos.x -= movementSpeed * std::cos(cameraRotation.y) * timestep;
			cameraPos.z += movementSpeed * std::sin(cameraRotation.y) * timestep;
		}
		if (Input.IsKeyPressed(eng::Keycode_Space))
			cameraPos.y += movementSpeed * timestep;
		if (Input.IsKeyPressed(eng::Keycode_LeftControl))
			cameraPos.y -= movementSpeed * timestep;
		if (Input.IsKeyPressed(eng::Keycode_S))
		{
			cameraPos.x += movementSpeed * std::sin(cameraRotation.y) * timestep;
			cameraPos.z += movementSpeed * std::cos(cameraRotation.y) * timestep;
		}
		if (Input.IsKeyPressed(eng::Keycode_W))
		{
			cameraPos.x -= movementSpeed * std::sin(cameraRotation.y) * timestep;
			cameraPos.z -= movementSpeed * std::cos(cameraRotation.y) * timestep;
		}
	}

	void WorldLayer::OnRender()
	{
		eng::Renderer::Clear();
		ChunkRenderer::RenderChunk(*m_Chunk, { 0, 0, 0 }, m_Camera, cameraPos, cameraRotation);
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
