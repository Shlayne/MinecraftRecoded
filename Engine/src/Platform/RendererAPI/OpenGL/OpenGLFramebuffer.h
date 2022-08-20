#pragma once

#include "Engine/Rendering/Framebuffer.h"
#include <glad/glad.h>

namespace eng
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specs);
		virtual ~OpenGLFramebuffer();
	public:
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(sint32 width, sint32 height) override;
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specs; }

		virtual uint32 GetColorAttachment(uint32 index = 0) const override;
		virtual uint32 GetDepthAttachment() const override { return m_DepthAttachment; }

		virtual sint32 GetColorPixel(sint32 x, sint32 y, uint32 index = 0) const override;

		virtual void ClearColorAttachment(sint32 value, uint32 index = 0) override;
	private:
		void Recreate();
		void Clear();
	private:
		FramebufferSpecification m_Specs;
		GLuint m_RendererID = 0;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;
		FramebufferTextureSpecification m_DepthAttachmentSpecs = FramebufferTextureFormat_None;

		std::vector<GLuint> m_ColorAttachments;
		GLuint m_DepthAttachment = 0;
	};
}
