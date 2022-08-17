#pragma once

#include "Engine/Rendering/RendererAPI.h"

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

		static void DrawIndexed();
	public: // Capabilities
		static sint32 GetMaxTextureSlots();
		static sint32 GetMaxTextureSize();
		static sint32 GetMaxFramebufferWidth();
		static sint32 GetMaxFramebufferHeight();
		static sint32 GetMaxFramebufferColorAttachments();
	private:
		friend class Application;
		static void Init();
		static void Shutdown();
	private:
		static Scope<RendererAPI> s_API;
	};
}
