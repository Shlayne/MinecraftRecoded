#include "Engine/pch.h"
#include "Engine/Rendering/Framebuffer.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLFramebuffer.h"

namespace eng
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& crSpecs)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return CreateRef<OpenGLFramebuffer>(crSpecs);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
