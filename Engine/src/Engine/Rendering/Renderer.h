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

		static void SetViewport(const glm::s32vec2& crPosition, const glm::s32vec2& crSize);

		static void Clear();
		static void ClearDepth();
		static void SetClearColor(const glm::vec4& crColor);

		static void DrawIndexed(const Ref<VertexArray>& crVertexArray, const Ref<IndexBuffer>& crIndexBuffer, uint32 offset = 0, uint32 count = 0, RendererPrimitive primitive = RendererPrimitive_Triangles);
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
