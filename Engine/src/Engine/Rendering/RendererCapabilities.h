#pragma once

#include "Engine/Core/Core.h"

namespace eng
{
	class RendererCapabilities
	{
	public:
		static sint32 GetMaxTextureSlots();
		static sint32 GetMaxTextureSize();
		static sint32 GetMaxTextureArrayLayers();
		static sint32 GetMaxFramebufferWidth();
		static sint32 GetMaxFramebufferHeight();
		static sint32 GetMaxFramebufferColorAttachments();
	private:
		RendererCapabilities() = delete;
		RendererCapabilities(const RendererCapabilities&) = delete;
		RendererCapabilities(RendererCapabilities&&) = delete;
		RendererCapabilities& operator=(const RendererCapabilities&) = delete;
		RendererCapabilities& operator=(RendererCapabilities&&) = delete;
		~RendererCapabilities() = delete;
	};
}
