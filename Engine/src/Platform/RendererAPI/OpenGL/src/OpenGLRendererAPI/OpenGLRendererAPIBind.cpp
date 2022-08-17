#include "OpenGLRendererAPI/OpenGLRendererAPIBind.h"
#include "OpenGLRendererAPI/OpenGLLogger.h"

namespace eng
{
#if ENABLE_LOGGING
	OpenGLRendererAPIBind::FGetCoreLogger OpenGLRendererAPIBind::s_GetCoreLogger = nullptr;
#endif
#if SYSTEM_WINDOWS
	OpenGLRendererAPIBind::FglfwMakeContextCurrent OpenGLRendererAPIBind::s_glfwMakeContextCurrent = nullptr;
	OpenGLRendererAPIBind::FglfwGetProcAddress OpenGLRendererAPIBind::s_glfwGetProcAddress = nullptr;
	OpenGLRendererAPIBind::FglfwSwapBuffers OpenGLRendererAPIBind::s_glfwSwapBuffers = nullptr;
#endif

	void OpenGLRendererAPIBind::SetFunctions
	(
#if ENABLE_LOGGING
		FGetCoreLogger fGetCoreLogger,
#endif
#if SYSTEM_WINDOWS
		FglfwMakeContextCurrent fglfwMakeContextCurrent,
		FglfwGetProcAddress fglfwGetProcAddress,
		FglfwSwapBuffers fglfwSwapBuffers
#endif
	)
	{
#if ENABLE_LOGGING
		s_GetCoreLogger = fGetCoreLogger;
#endif
#if SYSTEM_WINDOWS
		s_glfwMakeContextCurrent = fglfwMakeContextCurrent;
		s_glfwGetProcAddress = fglfwGetProcAddress;
		s_glfwSwapBuffers = fglfwSwapBuffers;
#endif
	}

#if ENABLE_LOGGING
	Ref<spdlog::logger>& OpenGLRendererAPIBind::GetCoreLogger()
	{
		CORE_ASSERT(s_GetCoreLogger != nullptr, "OpenGL Renderer API GetCoreLogger function was nullptr!");
		return s_GetCoreLogger();
	}
#endif
#if SYSTEM_WINDOWS
	void OpenGLRendererAPIBind::glfwMakeContextCurrent(GLFWwindow* pWindow)
	{
		CORE_ASSERT(s_glfwMakeContextCurrent != nullptr, "OpenGL Renderer API glfwMakeContextCurrent function was nullptr!");
		s_glfwMakeContextCurrent(pWindow);
	}

	GLFWglproc OpenGLRendererAPIBind::glfwGetProcAddress(const char* pProcName)
	{
		CORE_ASSERT(s_glfwGetProcAddress != nullptr, "OpenGL Renderer API glfwGetProcAddress function was nullptr!");
		return s_glfwGetProcAddress(pProcName);
	}

	void OpenGLRendererAPIBind::glfwSwapBuffers(GLFWwindow* pWindow)
	{
		CORE_ASSERT(s_glfwSwapBuffers != nullptr, "OpenGL Renderer API glfwSwapBuffers function was nullptr!");
		s_glfwSwapBuffers(pWindow);
	}
#endif
}
