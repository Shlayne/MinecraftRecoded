#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Engine/Rendering/VertexArray.h"

namespace eng
{
	class Renderer
	{
	public:
		static void EnableDepthTest();
		static void DisableDepthTest();
		static void EnableBlending();
		static void DisableBlending();
		static void EnableCulling();
		static void DisableCulling();

		static void SetViewport(const glm::s32vec2& position, const glm::s32vec2& size);

		static void Clear();
		static void ClearDepth();
		static void SetClearColor(const glm::vec4& color);

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<IndexBuffer>& indexBuffer, uint32 offset = 0, uint32 count = 0, RendererPrimitive primitive = RendererPrimitive_Triangles);
	private:
		friend class Application;
		static void Init();
		static void Shutdown();
	private:
		friend class RendererCapabilities;
		static Scope<RendererAPI> s_API;

		struct Cache
		{
			sint32 maxTextureSlots = 0;
			sint32 maxTextureSize = 0;
			sint32 maxTextureArrayLayers = 0;
			sint32 maxFramebufferWidth = 0;
			sint32 maxFramebufferHeight = 0;
			sint32 maxFramebufferColorAttachments = 0;
		};
		static Cache s_Cache;
	};
}
