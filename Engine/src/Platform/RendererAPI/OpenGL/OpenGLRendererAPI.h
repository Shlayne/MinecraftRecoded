#pragma once

#include "Engine/Rendering/RendererAPI.h"
#include <glad/glad.h>

namespace eng
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
	public:
		virtual void EnableDepthTest() override;
		virtual void DisableDepthTest() override;
		virtual void EnableBlending() override;
		virtual void DisableBlending() override;
		virtual void EnableCulling() override;
		virtual void DisableCulling() override;

		virtual void SetViewport(const glm::s32vec2& crPosition, const glm::s32vec2& crSize) override;

		virtual void Clear() override;
		virtual void ClearDepth() override;
		virtual void SetClearColor(const glm::vec4& crColor) override;

		virtual void DrawIndexed(const Ref<VertexArray>& crVertexArray, const Ref<IndexBuffer>& crIndexBuffer, uint32 offset, uint32 count, RendererPrimitive primitive) override;
	public: // Capabilities.
		virtual sint32 GetMaxTextureSlots() override;
		virtual sint32 GetMaxTextureSize() override;
		virtual sint32 GetMaxFramebufferWidth() override;
		virtual sint32 GetMaxFramebufferHeight() override;
		virtual sint32 GetMaxFramebufferColorAttachments() override;
	private:
		GLbitfield m_ClearBits = GL_COLOR_BUFFER_BIT;
	};
}
