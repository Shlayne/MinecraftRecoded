#include "Engine/pch.h"
#include "Engine/Rendering/Context.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace eng
{
	void WithContext(void* nativeWindow, const std::function<void()>& work)
	{
		GLFWwindow* context = static_cast<GLFWwindow*>(nativeWindow);

		GLFWwindow* currentContext = glfwGetCurrentContext();
		bool setNewContext = context != currentContext;

		if (setNewContext)
			glfwMakeContextCurrent(context);
		work();
		if (setNewContext)
			glfwMakeContextCurrent(currentContext);
	}

	void RemoveCurrentContext()
	{
		glfwMakeContextCurrent(NULL);
	}
}
