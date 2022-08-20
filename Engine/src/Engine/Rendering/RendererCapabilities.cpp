#include "Engine/pch.h"
#include "Engine/Rendering/RendererCapabilities.h"
#include "Engine/Rendering/Renderer.h"

namespace eng
{
	sint32 RendererCapabilities::GetMaxTextureSlots()
	{
		auto& maxTextureSlots = Renderer::s_Cache.maxTextureSlots;
		if (maxTextureSlots == 0)
			maxTextureSlots = Renderer::s_API->GetMaxTextureSlots();
		return maxTextureSlots;
	}

	sint32 RendererCapabilities::GetMaxTextureSize()
	{
		auto& maxTextureSize = Renderer::s_Cache.maxTextureSize;
		if (maxTextureSize == 0)
			maxTextureSize = Renderer::s_API->GetMaxTextureSize();
		return maxTextureSize;
	}

	sint32 RendererCapabilities::GetMaxTextureArrayLayers()
	{
		auto& maxTextureArrayLayers = Renderer::s_Cache.maxTextureArrayLayers;
		if (maxTextureArrayLayers == 0)
			maxTextureArrayLayers = Renderer::s_API->GetMaxTextureArrayLayers();
		return maxTextureArrayLayers;
	}

	sint32 RendererCapabilities::GetMaxFramebufferWidth()
	{
		auto& maxFramebufferWidth = Renderer::s_Cache.maxFramebufferWidth;
		if (maxFramebufferWidth == 0)
			maxFramebufferWidth = Renderer::s_API->GetMaxFramebufferWidth();
		return maxFramebufferWidth;
	}

	sint32 RendererCapabilities::GetMaxFramebufferHeight()
	{
		auto& maxFramebufferHeight = Renderer::s_Cache.maxFramebufferHeight;
		if (maxFramebufferHeight == 0)
			maxFramebufferHeight = Renderer::s_API->GetMaxFramebufferHeight();
		return maxFramebufferHeight;
	}

	sint32 RendererCapabilities::GetMaxFramebufferColorAttachments()
	{
		auto& maxFramebufferColorAttachments = Renderer::s_Cache.maxFramebufferColorAttachments;
		if (maxFramebufferColorAttachments == 0)
			maxFramebufferColorAttachments = Renderer::s_API->GetMaxFramebufferColorAttachments();
		return maxFramebufferColorAttachments;
	}
}
