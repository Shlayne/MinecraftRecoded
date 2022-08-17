#include "Engine/pch.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Core/Application.h"

namespace eng
{
	Renderer::Cache Renderer::s_Cache;
	Scope<RendererAPI> Renderer::s_API = nullptr;

	void Renderer::Init()
	{
		CORE_ASSERT(s_API == nullptr, "Attempted to recreate renderer!");

		s_API = RendererAPI::CreateScope();
	}

	void Renderer::Shutdown()
	{
		// May be called without Init being called.
		if (s_API == nullptr)
			return;

		DestroyScope(s_API);

		// Reset cached values.
		UNUSED(memset(&s_Cache, 0, sizeof(s_Cache)));
	}

	void Renderer::EnableDepthTest()
	{
		s_API->EnableDepthTest();
	}

	void Renderer::DisableDepthTest()
	{
		s_API->DisableDepthTest();
	}

	void Renderer::EnableBlending()
	{
		s_API->EnableBlending();
	}

	void Renderer::DisableBlending()
	{
		s_API->DisableBlending();
	}

	void Renderer::EnableCulling()
	{
		s_API->EnableCulling();
	}

	void Renderer::DisableCulling()
	{
		s_API->DisableCulling();
	}

	void Renderer::SetViewport(const glm::s32vec2& crPosition, const glm::s32vec2& crSize)
	{
		s_API->SetViewport(crPosition, crSize);
	}

	void Renderer::Clear()
	{
		s_API->Clear();
	}

	void Renderer::ClearDepth()
	{
		s_API->ClearDepth();
	}

	void Renderer::SetClearColor(const glm::vec4& crColor)
	{
		s_API->SetClearColor(crColor);
	}

	void Renderer::DrawIndexed(const Ref<VertexArray>& crVertexArray, const Ref<IndexBuffer>& crIndexBuffer, uint32 offset, uint32 count, RendererPrimitive primitive)
	{
		s_API->DrawIndexed(crVertexArray, crIndexBuffer, offset, count, primitive);
	}
}
