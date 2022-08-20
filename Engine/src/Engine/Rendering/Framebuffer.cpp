#include "Engine/pch.h"
#include "Engine/Rendering/Framebuffer.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLFramebuffer.h"

namespace eng
{
	Ref<Framebuffer> Framebuffer::CreateRef(const FramebufferSpecification& specs)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLFramebuffer>(specs);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
