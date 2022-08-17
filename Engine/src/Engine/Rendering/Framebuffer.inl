namespace eng
{
	static constexpr bool IsDepthFormat(FramebufferTextureFormat format)
	{
		switch (format)
		{
			case FramebufferTextureFormat_Depth24Stencil8:
				return true;
			case FramebufferTextureFormat_RGBA8:
			case FramebufferTextureFormat_RedInteger:
				return false;
		}

		CORE_ASSERT(false, "Unknown Framebuffer Texture Format!");
		return false;
	}

	constexpr FramebufferTextureSpecification::FramebufferTextureSpecification(FramebufferTextureFormat format) noexcept
		: format(format) {}

	constexpr FramebufferTextureSpecification::FramebufferTextureSpecification(FramebufferTextureFormat format, FramebufferFilterMode minFilter, FramebufferFilterMode magFilter, FramebufferWrapMode wrapS, FramebufferWrapMode wrapT) noexcept
		: format(format), minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}

	constexpr FramebufferAttachmentSpecification::FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) noexcept
		: attachments(attachments) {}
}
