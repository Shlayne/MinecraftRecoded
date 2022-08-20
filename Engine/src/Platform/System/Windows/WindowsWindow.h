#pragma once

#include "Engine/Core/Window.h"
#include "Engine/Rendering/Context.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace eng
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecifications& specs);
		virtual ~WindowsWindow();
	public:
		inline virtual sint32 GetWidth() const override { return m_State.current.size.x; }
		inline virtual sint32 GetHeight() const override { return m_State.current.size.y; }
		inline virtual glm::s32vec2 GetSize() const override { return m_State.current.size; }

		inline virtual sint32 GetFramebufferWidth() const override { return m_State.current.framebufferSize.x; }
		inline virtual sint32 GetFramebufferHeight() const override { return m_State.current.framebufferSize.y; }
		inline virtual glm::s32vec2 GetFramebufferSize() const override { return m_State.current.framebufferSize; }
	public:
		inline virtual bool IsFocused() const override { return m_State.focused; }
		inline virtual bool ContainsMouse() const override { return m_State.mouseContained; }
		inline virtual bool IsMinimized() const override { return m_State.minimized; }
		inline virtual bool IsMaximized() const override { return m_State.maximized; }

		inline virtual std::string_view GetTitle() const override { return m_State.title; }
		virtual void SetTitle(std::string_view title) override;

		virtual void SetIcon(const Ref<LocalTexture2D>& icon) override;
	public:
		inline virtual bool IsVsyncEnabled() const override { return m_State.vsync; }
		virtual void SetVsync(bool vsync) override;
		inline virtual void ToggleVSync() override { SetVsync(!IsVsyncEnabled()); }

		inline virtual bool IsResizable() const override { return m_State.resizable; }
		virtual void SetResizable(bool resizable) override;
		inline virtual void ToggleResizable() override { SetResizable(!IsResizable()); }

		inline virtual bool IsDecorated() const override { return m_State.decorated; }
		virtual void SetDecorated(bool decorated) override;
		inline virtual void ToggleDecorated() override { SetDecorated(!IsDecorated()); }

		inline virtual bool IsFullscreen() const override { return m_State.fullscreen; }
		virtual void SetFullscreen(bool fullscreen) override;
		inline virtual void ToggleFullscreen() override { SetFullscreen(!IsFullscreen()); }

		inline virtual bool IsMouseCaptured() const override { return m_State.mouseCaptured; }
		virtual void SetMouseCapture(bool mouseCaptured) override;
		inline virtual void ToggleMouseCapture() override { SetMouseCapture(!IsMouseCaptured()); }
	public:
		inline virtual Context& GetContext() override { return *m_Context; }
		inline virtual const Context& GetContext() const override { return *m_Context; }
		inline virtual void* GetNativeWindow() override { return m_Window; }
		inline virtual const void* GetNativeWindow() const override { return m_Window; }
	private:
		struct State
		{
			struct
			{
				glm::s32vec2 position{ 0 };
				glm::s32vec2 size{ 0 };
				glm::s32vec2 framebufferSize{ 0 };
			} current, preFullscreen;

			std::string title;

			bool vsync : 1 = false;
			bool resizable : 1 = false;
			bool decorated : 1 = false;
			bool fullscreen : 1 = false;
			bool mouseCaptured : 1 = false;
			bool mouseContained : 1 = false;
			bool focused : 1 = false;
			bool minimized : 1 = false;
			bool maximized : 1 = false;
		};
	private:
		GLFWwindow* m_Window = NULL;
		Scope<Context> m_Context = nullptr;
		State m_State;
	private:
		static void SetCallbacks(GLFWwindow* window);

		// Window event callbacks.
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowSizeCallback(GLFWwindow* window, sint32 width, sint32 height);
		static void WindowPosCallback(GLFWwindow* window, sint32 x, sint32 y);
		static void WindowFocusCallback(GLFWwindow* window, sint32 focused);
		static void WindowIconifyCallback(GLFWwindow* window, sint32 iconified);
		static void WindowMaximizeCallback(GLFWwindow* window, sint32 maximized);
		static void DropCallback(GLFWwindow* window, sint32 pathCount, const char** paths);
		static void FramebufferSizeCallback(GLFWwindow* window, sint32 width, sint32 height);
		static void WindowContentScaleCallback(GLFWwindow* window, float scaleX, float scaleY);
		static void WindowRefreshCallback(GLFWwindow* window);

		// Window key callbacks.
		static void KeyCallback(GLFWwindow* window, sint32 keycode, sint32 scancode, sint32 action, sint32 modifiers);
		static void CharCallback(GLFWwindow* window, uint32 codepoint);

		// Window mouse callbacks.
		static void MouseButtonCallback(GLFWwindow* window, sint32 button, sint32 action, sint32 modifiers);
		static void CursorPosCallback(GLFWwindow* window, double x, double y);
		static void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);
		static void CursorEnterCallback(GLFWwindow* window, sint32 entered);
	};
}
