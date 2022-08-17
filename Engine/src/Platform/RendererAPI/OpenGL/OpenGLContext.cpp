#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLContext.h"

namespace eng
{
	OpenGLContext::OpenGLContext(void* pNativeWindow)
#if SYSTEM_WINDOWS
		: m_pWindow(static_cast<GLFWwindow*>(pNativeWindow))
	{
		CORE_ASSERT(m_pWindow != NULL, "Context's Window is null!");
		glfwMakeContextCurrent(m_pWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status != 0, "Failed to initialize GLAD loader!");
	}
#endif

	void OpenGLContext::SwapBuffers()
	{
#if SYSTEM_WINDOWS
		glfwSwapBuffers(m_pWindow);
#endif
	}

	void OpenGLContext::MakeCurrent()
	{
#if SYSTEM_WINDOWS
		glfwMakeContextCurrent(m_pWindow);
#endif
	}
}
