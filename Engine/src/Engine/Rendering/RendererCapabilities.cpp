#include "Engine/pch.h"
#include "Engine/Rendering/RendererCapabilities.h"
#include "Engine/Rendering/Renderer.h"

namespace eng
{
	sint32 RendererCapabilities::GetMaxTextureSlots()
	{
		auto& rMaxTextureSlots = Renderer::s_Cache.maxTextureSlots;
		if (rMaxTextureSlots == 0)
			rMaxTextureSlots = Renderer::s_API->GetMaxTextureSlots();
		return rMaxTextureSlots;
	}

	sint32 RendererCapabilities::GetMaxTextureSize()
	{
		auto& rMaxTextureSize = Renderer::s_Cache.maxTextureSize;
		if (rMaxTextureSize == 0)
			rMaxTextureSize = Renderer::s_API->GetMaxTextureSize();
		return rMaxTextureSize;
	}

	sint32 RendererCapabilities::GetMaxTextureArrayLayers()
	{
		auto& rMaxTextureArrayLayers = Renderer::s_Cache.maxTextureArrayLayers;
		if (rMaxTextureArrayLayers == 0)
			rMaxTextureArrayLayers = Renderer::s_API->GetMaxTextureArrayLayers();
		return rMaxTextureArrayLayers;
	}

	sint32 RendererCapabilities::GetMaxFramebufferWidth()
	{
		auto& rMaxFramebufferWidth = Renderer::s_Cache.maxFramebufferWidth;
		if (rMaxFramebufferWidth == 0)
			rMaxFramebufferWidth = Renderer::s_API->GetMaxFramebufferWidth();
		return rMaxFramebufferWidth;
	}

	sint32 RendererCapabilities::GetMaxFramebufferHeight()
	{
		auto& rMaxFramebufferHeight = Renderer::s_Cache.maxFramebufferHeight;
		if (rMaxFramebufferHeight == 0)
			rMaxFramebufferHeight = Renderer::s_API->GetMaxFramebufferHeight();
		return rMaxFramebufferHeight;
	}

	sint32 RendererCapabilities::GetMaxFramebufferColorAttachments()
	{
		auto& rMaxFramebufferColorAttachments = Renderer::s_Cache.maxFramebufferColorAttachments;
		if (rMaxFramebufferColorAttachments == 0)
			rMaxFramebufferColorAttachments = Renderer::s_API->GetMaxFramebufferColorAttachments();
		return rMaxFramebufferColorAttachments;
	}
}
