#include "Engine/pch.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLTexture.h"

namespace eng
{
	TextureSpecification& TextureSpecification::operator=(const TextureSpecification& crSpecs) noexcept
	{
		if (this != &crSpecs)
		{
			texture = crSpecs.texture;
			minFilter = crSpecs.minFilter;
			magFilter = crSpecs.magFilter;
			wrapS = crSpecs.wrapS;
			wrapT = crSpecs.wrapT;
		}
		return *this;
	}

	TextureSpecification& TextureSpecification::operator=(TextureSpecification&& rrSpecs) noexcept
	{
		if (this != &rrSpecs)
		{
			texture = std::move(rrSpecs.texture);
			minFilter = rrSpecs.minFilter;
			magFilter = rrSpecs.magFilter;
			wrapS = rrSpecs.wrapS;
			wrapT = rrSpecs.wrapT;
		}
		return *this;
	}

	Ref<Texture2D> Texture2D::Create(const TextureSpecification& crSpecs)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return CreateRef<OpenGLTexture>(crSpecs);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<Texture2D> Texture2D::Create(const Ref<Framebuffer>& crFramebuffer, sint32 attachmentIndex)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return CreateRef<OpenGLTexture>(crFramebuffer, attachmentIndex);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
