#include "Engine/pch.h"
#include "Engine/Rendering/Context.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLContext.h"

namespace eng
{
	Scope<Context> Context::CreateScope(void* pNativeWindow)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateScope<OpenGLContext>(pNativeWindow);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
