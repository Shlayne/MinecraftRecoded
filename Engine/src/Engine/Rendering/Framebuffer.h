#pragma once

#include "Engine/Core/Core.h"
#include <vector>

namespace eng
{
	using FramebufferTextureFormat_ = uint8;
	enum FramebufferTextureFormat : FramebufferTextureFormat_
	{
		FramebufferTextureFormat_None = 0,

		// Color
		FramebufferTextureFormat_RGBA8,
		FramebufferTextureFormat_RedInteger,

		// Depth/Stencil
		FramebufferTextureFormat_Depth24Stencil8,

		// Defaults
		FramebufferTextureFormat_Color = FramebufferTextureFormat_RGBA8,
		FramebufferTextureFormat_Depth = FramebufferTextureFormat_Depth24Stencil8
	};

	using FramebufferFilterMode_ = uint8;
	enum FramebufferFilterMode : FramebufferFilterMode_
	{
		FramebufferFilterMode_Linear,
		FramebufferFilterMode_Nearest
	};

	using FramebufferWrapMode_ = uint8;
	enum FramebufferWrapMode : FramebufferWrapMode_
	{
		FramebufferWrapMode_ClampToEdge,
		FramebufferWrapMode_Repeat
	};

	struct FramebufferTextureSpecification
	{
		constexpr FramebufferTextureSpecification() noexcept = default;
		constexpr FramebufferTextureSpecification(FramebufferTextureFormat format) noexcept;
		constexpr FramebufferTextureSpecification(FramebufferTextureFormat format, FramebufferFilterMode minFilter, FramebufferFilterMode magFilter, FramebufferWrapMode wrapS, FramebufferWrapMode wrapT) noexcept;

		FramebufferTextureFormat format = FramebufferTextureFormat_None;
		FramebufferFilterMode minFilter = FramebufferFilterMode_Linear;
		FramebufferFilterMode magFilter = FramebufferFilterMode_Linear;
		FramebufferWrapMode wrapS = FramebufferWrapMode_ClampToEdge;
		FramebufferWrapMode wrapT = FramebufferWrapMode_ClampToEdge;
	};

	struct FramebufferAttachmentSpecification
	{
		constexpr FramebufferAttachmentSpecification() noexcept = default;
		constexpr FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) noexcept;

		std::vector<FramebufferTextureSpecification> attachments;
	};

	struct FramebufferSpecification
	{
		sint32 width = 0;
		sint32 height = 0;
		sint32 samples = 1;
		FramebufferAttachmentSpecification attachments;
	};

	static constexpr bool IsDepthFormat(FramebufferTextureFormat format);

	class Framebuffer
	{
	public:
		static Ref<Framebuffer> CreateRef(const FramebufferSpecification& specs);
		virtual ~Framebuffer() = default;
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(sint32 width, sint32 height) = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual uint32 GetColorAttachment(uint32 index = 0) const = 0;
		virtual uint32 GetDepthAttachment() const = 0;

		virtual sint32 GetColorPixel(sint32 x, sint32 y, uint32 index = 0) const = 0;

		virtual void ClearColorAttachment(sint32 value, uint32 index = 0) = 0;
	};
}

#include "Framebuffer.inl"
