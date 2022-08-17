#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLTexture.h"

namespace eng
{
	static constexpr GLenum UnconvertTextureFilterMode(TextureFilterMode filter)
	{
		switch (filter)
		{
			case TextureFilterMode_Linear:  return GL_LINEAR;
			case TextureFilterMode_Nearest: return GL_NEAREST;
		}

		CORE_ASSERT(false, "Unknown Texture Filter Mode!");
		return 0;
	}

	static constexpr GLenum UnconvertTextureWrapMode(TextureWrapMode wrap)
	{
		switch (wrap)
		{
			case TextureWrapMode_ClampToEdge: return GL_CLAMP_TO_EDGE;
			case TextureWrapMode_Repeat:      return GL_REPEAT;
		}

		CORE_ASSERT(false, "Unknown Texture Wrap Mode!");
		return 0;
	}

	static constexpr TextureFormat GetTextureFormat(sint32 channels)
	{
		switch (channels)
		{
			case 3: return TextureFormat_RGB8;
			case 4: return TextureFormat_RGBA8;
		}

		CORE_ASSERT(false, "Unconvertable number of channels!");
		return TextureFormat_None;
	}

	static constexpr void UnconvertTextureFormat(TextureFormat inFormat, GLenum& internalFormat, GLenum& format, GLenum& type)
	{
		switch (inFormat)
		{
			case TextureFormat_RGB8:
				internalFormat = GL_RGB8;
				format = GL_RGB;
				type = GL_UNSIGNED_BYTE;
				return;
			case TextureFormat_RGBA8:
				internalFormat = GL_RGBA8;
				format = GL_RGBA;
				type = GL_UNSIGNED_BYTE;
				return;
		}

		CORE_ASSERT(false, "Unknown Texture Format!");
	}

	OpenGLTexture::OpenGLTexture(const TextureSpecification& crSpecs)
		: m_Specs(crSpecs)
	{
		Init();
	}

	void OpenGLTexture::Init()
	{
		CORE_ASSERT(m_Specs.texture != nullptr && *m_Specs.texture, "Specifications texture is nullptr!");

		UnconvertTextureFormat(GetTextureFormat(m_Specs.texture->GetChannels()), m_InternalFormat, m_Format, m_Type);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Specs.texture->GetWidth(), m_Specs.texture->GetHeight());

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, UnconvertTextureFilterMode(m_Specs.minFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, UnconvertTextureFilterMode(m_Specs.magFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, UnconvertTextureWrapMode(m_Specs.wrapS));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, UnconvertTextureWrapMode(m_Specs.wrapT));

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.texture->GetWidth(), m_Specs.texture->GetHeight(), m_Format, m_Type, m_Specs.texture->GetData());
	}

	OpenGLTexture::OpenGLTexture(const Ref<Framebuffer>& crFramebuffer, sint32 attachmentIndex)
		: m_OwnsRendererID(false), m_RendererID(crFramebuffer->GetColorAttachment(attachmentIndex)) {}

	OpenGLTexture::~OpenGLTexture()
	{
		if (m_OwnsRendererID)
			glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture::Unbind(uint32 slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture::Update()
	{
		CORE_ASSERT(m_OwnsRendererID, "A Texture2D must have a local texture to update!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.texture->GetWidth(), m_Specs.texture->GetHeight(), m_Format, m_Type, m_Specs.texture->GetData());
	}
}
