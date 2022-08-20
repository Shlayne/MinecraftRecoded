#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLContext.h"

namespace eng
{
	OpenGLContext::OpenGLContext(void* nativeWindow)
#if SYSTEM_WINDOWS
		: m_Window(static_cast<GLFWwindow*>(nativeWindow))
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(m_Window != NULL, "Context's Window is null!");
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status != 0, "Failed to initialize GLAD loader!");
	}
#endif

	void OpenGLContext::SwapBuffers()
	{
		PROFILE_FUNCTION();

#if SYSTEM_WINDOWS
		glfwSwapBuffers(m_Window);
#endif
	}

	void OpenGLContext::MakeCurrent()
	{
		PROFILE_FUNCTION();

#if SYSTEM_WINDOWS
		glfwMakeContextCurrent(m_Window);
#endif
	}
}
