#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLFramebuffer.h"
#include "Engine/Rendering/RendererCapabilities.h"

namespace eng
{
	static constexpr GLenum GetOpenGLFilterMode(FramebufferFilterMode filter)
	{
		switch (filter)
		{
			case FramebufferFilterMode_Linear:  return GL_LINEAR;
			case FramebufferFilterMode_Nearest: return GL_NEAREST;
		}

		CORE_ASSERT(false, "Unknown Framebuffer Filter Mode!");
		return 0;
	}

	static constexpr GLenum UnconvertFramebufferWrapMode(FramebufferWrapMode wrap)
	{
		switch (wrap)
		{
			case FramebufferWrapMode_ClampToEdge: return GL_CLAMP_TO_EDGE;
			case FramebufferWrapMode_Repeat:      return GL_REPEAT;
		}

		CORE_ASSERT(false, "Unknown Framebuffer Wrap Mode!");
		return 0;
	}

	static constexpr GLenum UnconvertFramebufferTextureFormat(FramebufferTextureFormat format)
	{
		switch (format)
		{
			case FramebufferTextureFormat_RGBA8:      return GL_RGBA8;
			case FramebufferTextureFormat_RedInteger: return GL_RED_INTEGER;
		}

		CORE_ASSERT(false, "Unknown Framebuffer Texture Format!");
		return 0;
	}

	static constexpr GLenum GetTextureTarget(bool multisampled)
	{
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void CreateTextures(GLenum textureTarget, uint32* id, uint32 count)
	{
		glCreateTextures(textureTarget, count, id);
	}

	static void BindTexture(GLenum textureTarget, uint32 id)
	{
		glBindTexture(textureTarget, id);
	}

	static void AttachColorTexture(uint32 id, sint32 samples, GLenum internalFormat, GLenum format, sint32 width, sint32 height, FramebufferTextureSpecification specs, uint32 index)
	{
		bool multisampled = samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilterMode(specs.minFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilterMode(specs.magFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, UnconvertFramebufferWrapMode(specs.wrapS));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, UnconvertFramebufferWrapMode(specs.wrapT));
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GetTextureTarget(multisampled), id, 0);
	}

	static void AttachDepthTexture(uint32 id, sint32 samples, GLenum format, GLenum attachmentType, sint32 width, sint32 height, FramebufferTextureSpecification specs)
	{
		bool multisampled = samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilterMode(specs.minFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilterMode(specs.magFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, UnconvertFramebufferWrapMode(specs.wrapS));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, UnconvertFramebufferWrapMode(specs.wrapT));
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GetTextureTarget(multisampled), id, 0);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specs)
		: m_Specs(specs)
	{
		for (const auto& specification : m_Specs.attachments.attachments)
		{
			if (IsDepthFormat(specification.format))
			{
				CORE_ASSERT(m_DepthAttachmentSpecs.format == FramebufferTextureFormat_None, "Framebuffer already has depth attachment!");
				m_DepthAttachmentSpecs = specification;
			}
			else
				m_ColorAttachmentSpecs.push_back(specification);
		}

		Recreate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		Clear();
	}

	void OpenGLFramebuffer::Recreate()
	{
		Clear();

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// Attachments
		bool multisampled = m_Specs.samples > 1;
		GLenum textureTarget = GetTextureTarget(multisampled);

		if (m_ColorAttachmentSpecs.size() != 0)
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			CreateTextures(textureTarget, m_ColorAttachments.data(), static_cast<uint32>(m_ColorAttachments.size()));

			for (uint32 i = 0; i < static_cast<uint32>(m_ColorAttachments.size()); i++)
			{
				BindTexture(textureTarget, m_ColorAttachments[i]);

				switch (m_ColorAttachmentSpecs[i].format)
				{
					case FramebufferTextureFormat_RGBA8:
						AttachColorTexture(m_ColorAttachments[i], m_Specs.samples, GL_RGBA8, GL_RGBA, m_Specs.width, m_Specs.height, m_ColorAttachmentSpecs[i], i);
						break;
					case FramebufferTextureFormat_RedInteger:
						AttachColorTexture(m_ColorAttachments[i], m_Specs.samples, GL_R32I, GL_RED_INTEGER, m_Specs.width, m_Specs.height, m_ColorAttachmentSpecs[i], i);
						break;
				}
			}
		}
	
		if (m_DepthAttachmentSpecs.format != FramebufferTextureFormat_None)
		{
			CreateTextures(textureTarget, &m_DepthAttachment, 1);
			BindTexture(textureTarget, m_DepthAttachment);

			switch (m_DepthAttachmentSpecs.format)
			{
				case FramebufferTextureFormat_Depth24Stencil8:
					AttachDepthTexture(m_DepthAttachment, m_Specs.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specs.width, m_Specs.height, m_DepthAttachmentSpecs);
					break;
			}
		}

		if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}
		else
		{
			sint32 maxColorAttachments = RendererCapabilities::GetMaxFramebufferColorAttachments();
			CORE_ASSERT(static_cast<sint32>(m_ColorAttachments.size()) <= maxColorAttachments, "Too many Framebuffer color attachments!");
			std::vector<GLenum> buffers;
			for (uint32 i = 0; i < static_cast<uint32>(m_ColorAttachments.size()); i++)
				buffers.push_back(static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + i));
			glDrawBuffers(static_cast<GLsizei>(m_ColorAttachments.size()), buffers.data());
		}

		CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Clear()
	{
		if (m_RendererID != 0)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(static_cast<GLsizei>(m_ColorAttachments.size()), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_RendererID = 0;
			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specs.width, m_Specs.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32 OpenGLFramebuffer::GetColorAttachment(uint32 index) const
	{
		CORE_ASSERT(index < static_cast<uint32>(m_ColorAttachments.size()), "Framebuffer color attachment index out of bounds.");
		return m_ColorAttachments[index];
	}

	void OpenGLFramebuffer::Resize(sint32 width, sint32 height)
	{
		CORE_ASSERT(width > 0, "Framebuffer width={0} must be positive.", width);
		CORE_ASSERT(width <= RendererCapabilities::GetMaxFramebufferWidth(), "Framebuffer width={0} cannot be greater than {1}!", width, RendererCapabilities::GetMaxFramebufferWidth());
		CORE_ASSERT(height > 0, "Framebuffer height={0} must be positive.", height);
		CORE_ASSERT(height <= RendererCapabilities::GetMaxFramebufferHeight(), "Framebuffer height={0} cannot be greater than {1}!", height, RendererCapabilities::GetMaxFramebufferHeight());

		m_Specs.width = width;
		m_Specs.height = height;
		Recreate();
	}

	sint32 OpenGLFramebuffer::GetColorPixel(sint32 x, sint32 y, uint32 index) const
	{
		CORE_ASSERT(index < m_ColorAttachments.size(), "Framebuffer color attachment index out of bounds!");
		CORE_ASSERT(x >= 0, "Framebuffer sample x={0} cannot be negative.", x);
		CORE_ASSERT(x < m_Specs.width, "Framebuffer sample x={0} cannot larger than.", m_Specs.width - 1);
		CORE_ASSERT(y >= 0, "Framebuffer sample y={0} cannot be negative.", y);
		CORE_ASSERT(y < m_Specs.width, "Framebuffer sample y={0} cannot larger than.", m_Specs.height - 1);

		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		GLenum format = UnconvertFramebufferTextureFormat(m_ColorAttachmentSpecs[index].format);
		sint32 pixel = 0;
		glReadPixels(x, y, 1, 1, format, GL_INT, &pixel);
		return pixel;
	}

	void OpenGLFramebuffer::ClearColorAttachment(sint32 value, uint32 index)
	{
		CORE_ASSERT(index < m_ColorAttachments.size(), "Framebuffer color attachment index out of bounds!");

		GLenum format = UnconvertFramebufferTextureFormat(m_ColorAttachmentSpecs[index].format);
		glClearTexImage(m_ColorAttachments[index], 0, format, GL_INT, &value);
	}
}
