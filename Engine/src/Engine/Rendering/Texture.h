#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/Framebuffer.h"
#include "Engine/Rendering/LocalTexture2D.h"

namespace eng
{
	using TextureFormat_ = uint8;
	enum TextureFormat : TextureFormat_
	{
		TextureFormat_None = 0,

		TextureFormat_RGB8,
		TextureFormat_RGBA8
	};

	using TextureFilterMode_ = uint8;
	enum TextureFilterMode : TextureFilterMode_
	{
		TextureFilterMode_Linear,
		TextureFilterMode_Nearest
	};

	using TextureWrapMode_ = uint8;
	enum TextureWrapMode : TextureWrapMode_
	{
		TextureWrapMode_ClampToEdge,
		TextureWrapMode_Repeat
	};

	struct TextureSpecification
	{
		constexpr TextureSpecification() noexcept = default;
		TextureSpecification(const Ref<LocalTexture2D>& texture) noexcept
			: texture(texture) {}
		TextureSpecification(Ref<LocalTexture2D>&& texture) noexcept
			: texture(std::move(texture)) {}
		TextureSpecification(const Ref<LocalTexture2D>& texture, TextureFilterMode minFilter, TextureFilterMode magFilter, TextureWrapMode wrapS, TextureWrapMode wrapT) noexcept
			: texture(texture), minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}
		TextureSpecification(Ref<LocalTexture2D>& texture, TextureFilterMode minFilter, TextureFilterMode magFilter, TextureWrapMode wrapS, TextureWrapMode wrapT) noexcept
			: texture(std::move(texture)), minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}
		TextureSpecification(TextureFilterMode minFilter, TextureFilterMode magFilter, TextureWrapMode wrapS, TextureWrapMode wrapT) noexcept
			: minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}
		TextureSpecification(const TextureSpecification& specs) noexcept
			: texture(specs.texture), minFilter(specs.minFilter), magFilter(specs.magFilter), wrapS(specs.wrapS), wrapT(specs.wrapT) {}
		TextureSpecification(TextureSpecification&& specs) noexcept
			: texture(std::move(specs.texture)), minFilter(specs.minFilter), magFilter(specs.magFilter), wrapS(specs.wrapS), wrapT(specs.wrapT) {}
		TextureSpecification& operator=(const TextureSpecification& specs) noexcept;
		TextureSpecification& operator=(TextureSpecification&& specs) noexcept;

		Ref<LocalTexture2D> texture = nullptr;
		TextureFilterMode minFilter = TextureFilterMode_Linear;
		TextureFilterMode magFilter = TextureFilterMode_Linear;
		TextureWrapMode wrapS = TextureWrapMode_ClampToEdge;
		TextureWrapMode wrapT = TextureWrapMode_ClampToEdge;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32 slot = 0) const = 0;
		virtual void Unbind(uint32 slot = 0) const = 0;

		virtual uint32 GetRendererID() const = 0;
		virtual const Ref<LocalTexture2D>& GetTexture() const = 0;
		virtual const TextureSpecification& GetSpecification() const = 0;

		// Call this when you want to update the internal
		// texture after the the local texture has updated.
		// Only call if this was not constructed with a Framebuffer.
		virtual void Update() = 0;

		// Returns true if this texture was constructed with a Framebuffer, false otherwise.
		virtual bool IsFramebufferTexture() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> CreateRef(const TextureSpecification& specs);
		static Ref<Texture2D> CreateRef(const Ref<Framebuffer>& framebuffer, sint32 attachmentIndex);
	};
}
