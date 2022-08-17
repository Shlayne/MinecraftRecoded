#pragma once

// This should always be included, and be the second to last include.

#if OPENGL_RENDERER_API_EXPORT
	#define OPENGL_RENDERER_API __declspec(dllexport)
#else
	#define OPENGL_RENDERER_API __declspec(dllimport)
#endif

#include "Engine/Core/Core.h"
#if SYSTEM_WINDOWS
	#define GLFW_INCLUDE_NONE
	#include <glfw/glfw3.h>
#endif

namespace eng
{
	class OPENGL_RENDERER_API OpenGLRendererAPIBind
	{
	public: // Function type definitions.
#if ENABLE_LOGGING
		using FGetCoreLogger = Ref<spdlog::logger>&(*)();
#endif
#if SYSTEM_WINDOWS
		using FglfwMakeContextCurrent = void(*)(GLFWwindow*);
		using FglfwGetProcAddress = GLFWglproc(*)(const char*);
		using FglfwSwapBuffers = void(*)(GLFWwindow*);
#endif
	public: // Internal function calls.
#if ENABLE_LOGGING
		static Ref<spdlog::logger>& GetCoreLogger();
#endif
#if SYSTEM_WINDOWS
		static void glfwMakeContextCurrent(GLFWwindow* pWindow);
		static GLFWglproc glfwGetProcAddress(const char* pProcName);
		static void glfwSwapBuffers(GLFWwindow* pWindow);
#endif
	private: // Function setup.
		static void SetFunctions
		(
#if ENABLE_LOGGING
			FGetCoreLogger fGetCoreLogger,
#endif
#if SYSTEM_WINDOWS
			FglfwMakeContextCurrent fglfwMakeContextCurrent,
			FglfwGetProcAddress fglfwGetProcAddress,
			FglfwSwapBuffers fglfwSwapBuffers
#endif
		);
	private: // Function pointers themselves.
#if ENABLE_LOGGING
		static FGetCoreLogger s_GetCoreLogger;
#endif
#if SYSTEM_WINDOWS
		static FglfwMakeContextCurrent s_glfwMakeContextCurrent;
		static FglfwGetProcAddress s_glfwGetProcAddress;
		static FglfwSwapBuffers s_glfwSwapBuffers;
#endif
	private:
		OpenGLRendererAPIBind() = delete;
		OpenGLRendererAPIBind(const OpenGLRendererAPIBind&) = delete;
		OpenGLRendererAPIBind(OpenGLRendererAPIBind&&) = delete;
		OpenGLRendererAPIBind& operator=(const OpenGLRendererAPIBind&) = delete;
		OpenGLRendererAPIBind& operator=(OpenGLRendererAPIBind&&) = delete;
		~OpenGLRendererAPIBind() = delete;

		friend class RendererAPI;
	};

	// Just to reduce function call code.
	using Bind = OpenGLRendererAPIBind;
}
