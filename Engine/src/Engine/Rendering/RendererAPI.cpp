#include "Engine/pch.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLRendererAPI.h"

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
			case API_OpenGL: break;
			default: return false;
		}

		return true;
	}

	Scope<RendererAPI> RendererAPI::CreateScope()
	{
		switch (s_API)
		{
			case API_OpenGL: return eng::CreateScope<OpenGLRendererAPI>();
			UNKNOWN_RENDERER_API(s_API, nullptr);
		}
	}
}
