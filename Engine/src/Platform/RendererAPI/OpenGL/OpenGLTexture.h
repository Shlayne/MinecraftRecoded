#pragma once

#include "Engine/Rendering/Texture.h"
#include <glad/glad.h>

namespace eng
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const TextureSpecification& crSpecs);
		OpenGLTexture(const Ref<Framebuffer>& crFramebuffer, sint32 attachmentIndex);
		virtual ~OpenGLTexture();
	public:
		virtual void Bind(uint32 slot = 0) const override;
		virtual void Unbind(uint32 slot = 0) const override;

		virtual uint32 GetRendererID() const override { return static_cast<uint32>(m_RendererID); }
		virtual const Ref<LocalTexture2D>& GetTexture() const override { return m_Specs.texture; }
		virtual const TextureSpecification& GetSpecification() const override { return m_Specs; }

		virtual void Update() override;
		virtual bool IsFramebufferTexture() const override { return !m_OwnsRendererID; }
	private:
		void Init();
	private:
		TextureSpecification m_Specs;
		bool m_OwnsRendererID = true;

		GLuint m_RendererID = 0;
		GLuint m_InternalFormat = 0;
		GLuint m_Format = 0;
		GLuint m_Type = 0;
	};
}
