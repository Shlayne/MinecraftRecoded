#include "Engine/pch.h"
#include "Engine/Rendering/RendererAPI.h"
#if SUPPORTS_OPENGL
	#include "OpenGLRendererAPI/OpenGLRendererAPIBind.h"
#endif
#include <libloaderapi.h>

namespace eng
{
	static HMODULE s_hLibModule = NULL;

	void RendererAPI::LoadAPI()
	{
		CORE_ASSERT(s_hLibModule == NULL, "Attempted to load Renderer API ({0}) without restarting!", +RendererAPI::GetAPI());

		switch (RendererAPI::GetAPI())
		{
#if SUPPORTS_OPENGL
		case API_OpenGL:
			s_hLibModule = LoadLibraryW(L"OpenGLRendererAPI.dll");
			CORE_ASSERT(s_hLibModule != NULL, "Failed to load OpenGL Renderer API dll!");

			OpenGLRendererAPIBind::SetFunctions(
#if ENABLE_LOGGING
				&Logger::GetCoreLogger,
#endif
#if SYSTEM_WINDOWS
				&glfwMakeContextCurrent,
				&glfwGetProcAddress,
				&glfwSwapBuffers
#endif
			);

			break;
#endif
		UNKNOWN_RENDERER_API(RendererAPI::GetAPI());
		}
	}

	void RendererAPI::UnloadAPI()
	{
		CORE_ASSERT(s_hLibModule != NULL, "Attempted to unload Renderer API without having loaded it!");
		BOOL status = FreeLibrary(s_hLibModule);
		CORE_ASSERT(status != 0, "Failed to free Renderer API dll library!");
		s_hLibModule = NULL;
	}
}
