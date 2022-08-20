#include "Engine/pch.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLTexture.h"

namespace eng
{
	TextureSpecification& TextureSpecification::operator=(const TextureSpecification& specs) noexcept
	{
		if (this != &specs)
		{
			texture = specs.texture;
			minFilter = specs.minFilter;
			magFilter = specs.magFilter;
			wrapS = specs.wrapS;
			wrapT = specs.wrapT;
		}
		return *this;
	}

	TextureSpecification& TextureSpecification::operator=(TextureSpecification&& specs) noexcept
	{
		if (this != &specs)
		{
			texture = std::move(specs.texture);
			minFilter = specs.minFilter;
			magFilter = specs.magFilter;
			wrapS = specs.wrapS;
			wrapT = specs.wrapT;
		}
		return *this;
	}

	Ref<Texture2D> Texture2D::CreateRef(const TextureSpecification& specs)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLTexture>(specs);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<Texture2D> Texture2D::CreateRef(const Ref<Framebuffer>& framebuffer, sint32 attachmentIndex)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLTexture>(framebuffer, attachmentIndex);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
