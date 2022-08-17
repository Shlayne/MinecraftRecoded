#include "Engine/pch.h"
#include "Engine/Rendering/RendererAPI.h"
#if SUPPORTS_OPENGL
	#include "OpenGLRendererAPI/OpenGLRendererAPI.h"
#endif

namespace eng
{
	static RendererAPI::API s_API = RendererAPI::API_None;

	RendererAPI::API RendererAPI::GetAPI()
	{
		return s_API;
	}

	bool RendererAPI::SetAPI(API api)
	{
		if (!SupportsAPI(api))
			return false;
		s_API = api;
		return true;
	}

	bool RendererAPI::SupportsAPI(API api)
	{
		switch (api)
		{
#if SUPPORTS_OPENGL
		case API_OpenGL: break;
#endif
		default: return false;
		}

		return true;
	}

	Scope<RendererAPI> RendererAPI::CreateScope()
	{
		switch (s_API)
		{
#if SUPPORTS_OPENGL
		case API_OpenGL: return eng::CreateScope<OpenGLRendererAPI>();
#endif
		UNKNOWN_RENDERER_API(s_API, nullptr);
		}
	}
}
