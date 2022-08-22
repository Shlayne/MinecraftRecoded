#include "Engine/pch.h"
#include "Platform/System/Windows/WindowsWindow.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Events/KeyEvents.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/System/Windows/WindowsConversions.h"

namespace eng
{
	WindowsWindow::WindowsWindow(const WindowSpecifications& specs)
	{
		PROFILE_FUNCTION();

		m_State.current.size = { specs.width, specs.height };
		m_State.title = specs.title;
		m_State.resizable = specs.resizable;
		m_State.decorated = specs.decorated;
		m_State.focused = specs.focusOnShow;

		glfwWindowHint(GLFW_RESIZABLE, m_State.resizable);
		glfwWindowHint(GLFW_DECORATED, m_State.decorated);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, m_State.focused);
		glfwWindowHint(GLFW_VISIBLE, false);
#if CONFIG_PROFILE || CONFIG_DEBUG
		if (RendererAPI::GetAPI() == RendererAPI::API_OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

#if ENABLE_LOGGING
		if (glfwGetCurrentContext() != NULL)
			LOG_CORE_WARN("Window created on thread with rendering context already current.");
#endif

		{
			PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow(m_State.current.size.x, m_State.current.size.y, m_State.title.c_str(), NULL, NULL);
		}
		CORE_ASSERT(m_Window != NULL, "Failed to create window!");

		glm::s32vec2 position{ 0 };
		glm::s32vec2 size{ 0 };
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &position.x, &position.y, &size.x, &size.y);
		sint32 left, top, right, bottom;
		glfwGetWindowFrameSize(m_Window, &left, &top, &right, &bottom);
		glm::s32vec2 windowFrameSize{ right - left, bottom - (top + 8) };
		// The +8 for top is for the invisible windows 10 borders for resizing the window.
		// Only left, right, and bottom have it, but not top. And since bottom has it and
		// not top, the window is pushed up by 8 / 2 = 4 pixels.

		m_State.current.position = position + (size - m_State.current.size - windowFrameSize) / 2;
		glfwSetWindowPos(m_Window, m_State.current.position.x, m_State.current.position.y);

		glfwSetInputMode(m_Window, GLFW_LOCK_KEY_MODS, true);
		glfwSetWindowUserPointer(m_Window, &m_State);

		{
			PROFILE_SCOPE("Context::CreateScope");
			m_Context = Context::CreateScope(m_Window);
		}

		if (specs.vsync)
			SetVsync(true);
		if (specs.mouseCaptured)
			SetMouseCapture(true);

		if (specs.maximizeOnShow)
		{
			glfwMaximizeWindow(m_Window);
			glfwGetWindowPos(m_Window, &m_State.current.position.x, &m_State.current.position.y);
			glfwGetWindowSize(m_Window, &m_State.current.size.x, &m_State.current.size.y);
			m_State.maximized = true;
		}

		glfwGetFramebufferSize(m_Window, &m_State.current.framebufferSize.x, &m_State.current.framebufferSize.y);

		if (specs.fullscreenOnShow)
			SetFullscreen(true);

		SetCallbacks(m_Window);
		glfwShowWindow(m_Window);
	}

	WindowsWindow::~WindowsWindow()
	{
		PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		m_State.title = title;
		glfwSetWindowTitle(m_Window, title.data());
	}

	void WindowsWindow::SetIcon(const Ref<LocalTexture2D>& icon)
	{
		GLFWimage glfwIcon{};
		glfwIcon.width = icon->GetWidth();
		glfwIcon.height = icon->GetHeight();
		glfwIcon.pixels = icon->GetData();
		glfwSetWindowIcon(m_Window, 1, &glfwIcon);
	}

	void WindowsWindow::SetVsync(bool vsync)
	{
		WithContext(m_Window, [vsync]()
		{
			glfwSwapInterval(!!vsync);
		});
		m_State.vsync = vsync;
	}

	void WindowsWindow::SetResizable(bool resizable)
	{
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, resizable);
		m_State.resizable = resizable;
	}

	void WindowsWindow::SetDecorated(bool decorated)
	{
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, decorated);
		m_State.decorated = decorated;
	}

	void WindowsWindow::SetFullscreen(bool fullscreen)
	{
		GLFWmonitor* monitor = NULL;
		sint32 refreshRate = GLFW_DONT_CARE;

		if (fullscreen)
		{
			// From: https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
			// Get the monitor that most of the window is on.
			// On Windows, MonitorFromWindow(window->win32.handle, MONITOR_DEFAULTTONEAREST)
			// does exactly this, but returns the windows monitor handle as opposed to the glfw monitor.
			// However, glfw 3.3.8 doesn't support using that in this way.

			sint32 largestOverlap = sint32_min;
			const GLFWvidmode* videoMode = NULL;

			sint32 monitorCount;
			GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

			for (sint32 i = 0; i < monitorCount; i++)
			{
				GLFWmonitor* currentMonitor = monitors[i];
				const GLFWvidmode* currentVideoMode = glfwGetVideoMode(currentMonitor);
				glm::s32vec2 videoModeSize{ currentVideoMode->width, currentVideoMode->height };

				glm::s32vec2 monitorPos;
				glfwGetMonitorPos(currentMonitor, &monitorPos.x, &monitorPos.y);

				glm::s32vec2 overlapSize = glm::max(glm::s32vec2{ 0 },
					glm::min(
						m_State.current.position + m_State.current.size,
						monitorPos + videoModeSize
					) - glm::max(m_State.current.position, monitorPos)
				);

				sint32 overlap = overlapSize.x * overlapSize.y;
				if (overlap > largestOverlap)
				{
					largestOverlap = overlap;
					monitor = currentMonitor;
					videoMode = currentVideoMode;
				}
			}

			CORE_ASSERT(monitor != NULL, "Could not find suitable monitor for window to fullscreen into.");
			m_State.preFullscreen = m_State.current;
			m_State.current.position = { 0, 0 };
			m_State.current.size = { videoMode->width, videoMode->height };
			refreshRate = videoMode->refreshRate;
		}
		else
			m_State.current = m_State.preFullscreen;

		glfwSetWindowMonitor(
			m_Window, monitor,
			m_State.current.position.x, m_State.current.position.y,
			m_State.current.size.x, m_State.current.size.y,
			refreshRate
		);

		glfwGetFramebufferSize(m_Window, &m_State.current.framebufferSize.x, &m_State.current.framebufferSize.y);
		SetVsync(IsVsyncEnabled()); // TODO: remove

		m_State.fullscreen = fullscreen;
	}

	void WindowsWindow::SetMouseCapture(bool mouseCaptured)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, mouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		m_State.mouseCaptured = mouseCaptured;
	}

	void WindowsWindow::SetCallbacks(GLFWwindow* window)
	{
		// Window Events
		glfwSetWindowCloseCallback(window, WindowCloseCallback);
		glfwSetWindowSizeCallback(window, WindowSizeCallback);
		glfwSetWindowPosCallback(window, WindowPosCallback);
		glfwSetWindowFocusCallback(window, WindowFocusCallback);
		glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
		glfwSetWindowMaximizeCallback(window, WindowMaximizeCallback);
		glfwSetDropCallback(window, DropCallback);
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		glfwSetWindowContentScaleCallback(window, WindowContentScaleCallback);
		glfwSetWindowRefreshCallback(window, WindowRefreshCallback);

		// Key Events
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCharCallback(window, CharCallback);

		// Mouse Events
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetScrollCallback(window, ScrollCallback);
		glfwSetCursorEnterCallback(window, CursorEnterCallback);
	}

	void WindowsWindow::WindowCloseCallback(GLFWwindow* window)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			WindowCloseEvent event(window);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowSizeCallback(GLFWwindow* window, sint32 width, sint32 height)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->current.size = { width, height };

			WindowResizeEvent event(window, width, height);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowPosCallback(GLFWwindow* window, sint32 x, sint32 y)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->current.position = { x, y };

			WindowMoveEvent event(window, x, y);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowFocusCallback(GLFWwindow* window, sint32 focused)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->focused = focused == GLFW_TRUE;

			WindowFocusEvent event(window, state->focused);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowIconifyCallback(GLFWwindow* window, sint32 iconified)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->minimized = iconified == GLFW_TRUE;

			WindowMinimizeEvent event(window, state->minimized);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowMaximizeCallback(GLFWwindow* window, sint32 maximized)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->maximized = maximized == GLFW_TRUE;

			WindowMaximizeEvent event(window, state->maximized);
			OnEvent(event);
		}
	}

	void WindowsWindow::DropCallback(GLFWwindow* window, sint32 count, const char** ppPaths)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			WindowPathDropEvent event(window, count, ppPaths);
			OnEvent(event);
		}
	}

	void WindowsWindow::FramebufferSizeCallback(GLFWwindow* window, sint32 width, sint32 height)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->current.framebufferSize = { width, height };

			WindowFramebufferResizeEvent event(window, width, height);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowContentScaleCallback(GLFWwindow* window, float scaleX, float scaleY)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			WindowContentScaleEvent event(window, scaleX, scaleY);
			OnEvent(event);
		}
	}

	void WindowsWindow::WindowRefreshCallback(GLFWwindow* window)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			WindowRefreshEvent event(window);
			OnEvent(event);
		}
	}

	void WindowsWindow::KeyCallback(GLFWwindow* window, sint32 keycode, sint32 scancode, sint32 action, sint32 modifiers)
	{
		State* state = static_cast<State*>(glfwGetWindowUserPointer(window));
		if (state != nullptr && keycode != GLFW_KEY_UNKNOWN)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent event(window, ConvertKeycode(keycode), ConvertModifiers(modifiers));
					OnEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyRepeatEvent event(window, ConvertKeycode(keycode), ConvertModifiers(modifiers));
					OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent event(window, ConvertKeycode(keycode), ConvertModifiers(modifiers));
					OnEvent(event);
					break;
				}
			}
		}
	}

	void WindowsWindow::CharCallback(GLFWwindow* window, uint32 codepoint)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			CharTypeEvent event(window, codepoint);
			OnEvent(event);
		}
	}

	void WindowsWindow::MouseButtonCallback(GLFWwindow* window, sint32 button, sint32 action, sint32 modifiers)
	{
		State* state = static_cast<State*>(glfwGetWindowUserPointer(window));
		if (state != nullptr)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent event(window, ConvertMouseButton(button), ConvertModifiers(modifiers));
					OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent event(window, ConvertMouseButton(button), ConvertModifiers(modifiers));
					OnEvent(event);
					break;
				}
			}
		}
	}

	void WindowsWindow::CursorPosCallback(GLFWwindow* window, double x, double y)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			MouseMoveEvent event(window, static_cast<float>(x), static_cast<float>(y));
			OnEvent(event);
		}
	}

	void WindowsWindow::ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			MouseScrollEvent event(window, static_cast<float>(offsetX), static_cast<float>(offsetY));
			OnEvent(event);
		}
	}

	void WindowsWindow::CursorEnterCallback(GLFWwindow* window, sint32 entered)
	{
		if (State* state = static_cast<State*>(glfwGetWindowUserPointer(window)))
		{
			state->mouseContained = entered == GLFW_TRUE;

			MouseEnterEvent event(window, state->mouseContained);
			OnEvent(event);
		}
	}
}
