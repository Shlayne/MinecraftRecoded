#pragma once

#include "Engine/Rendering/Context.h"
#include <glad/glad.h>
#if SYSTEM_WINDOWS
	#define GLFW_INCLUDE_NONE
	#include <glfw/glfw3.h>
#endif

namespace eng
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(void* nativeWindow);
	public:
		virtual void SwapBuffers() override;
		virtual void MakeCurrent() override;
	private:
#if SYSTEM_WINDOWS
		GLFWwindow* m_Window;
#endif
	};
}
