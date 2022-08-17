#include "Engine/pch.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Core/Application.h"

namespace eng
{
	struct Cache
	{
		sint32 maxTextureSlots = 0;
		sint32 maxTextureSize = 0;
		sint32 maxFramebufferWidth = 0;
		sint32 maxFramebufferHeight = 0;
		sint32 maxFramebufferColorAttachments = 0;
	};
	static Cache s_Cache;

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

	void Renderer::DrawIndexed()
	{
		s_API->DrawIndexed();
	}

	sint32 Renderer::GetMaxTextureSlots()
	{
		if (s_Cache.maxTextureSlots != 0)
			s_Cache.maxTextureSlots = s_API->GetMaxTextureSlots();
		return s_Cache.maxTextureSlots;
	}

	sint32 Renderer::GetMaxTextureSize()
	{
		if (s_Cache.maxTextureSize != 0)
			s_Cache.maxTextureSize = s_API->GetMaxTextureSize();
		return s_Cache.maxTextureSize;
	}

	sint32 Renderer::GetMaxFramebufferWidth()
	{
		if (s_Cache.maxFramebufferWidth != 0)
			s_Cache.maxFramebufferWidth = s_API->GetMaxFramebufferWidth();
		return s_Cache.maxFramebufferWidth;
	}

	sint32 Renderer::GetMaxFramebufferHeight()
	{
		if (s_Cache.maxFramebufferHeight != 0)
			s_Cache.maxFramebufferHeight = s_API->GetMaxFramebufferHeight();
		return s_Cache.maxFramebufferHeight;
	}

	sint32 Renderer::GetMaxFramebufferColorAttachments()
	{
		if (s_Cache.maxFramebufferColorAttachments == 0)
			s_Cache.maxFramebufferColorAttachments = s_API->GetMaxFramebufferColorAttachments();
		return s_Cache.maxFramebufferColorAttachments;
	}
}
