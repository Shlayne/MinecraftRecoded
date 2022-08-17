#include "Engine/pch.h"
#include "Engine/Rendering/Context.h"
#include "Engine/Rendering/RendererAPI.h"
#if SUPPORTS_OPENGL
	#include "OpenGLRendererAPI/OpenGLContext.h"
#endif

namespace eng
{
	Scope<Context> Context::CreateScope(void* pNativeWindow)
	{
		switch (RendererAPI::GetAPI())
		{
#if SUPPORTS_OPENGL
		case RendererAPI::API_OpenGL: return eng::CreateScope<OpenGLContext>(pNativeWindow);
#endif
		UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
