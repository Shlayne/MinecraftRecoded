#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Core/MouseButtons.h"
#include "Engine/Core/Modifiers.h"

namespace eng
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent(void* nativeWindow)
			: m_NativeWindow(nativeWindow) {}
	public:
		inline void* GetNativeWindow() const { return m_NativeWindow; }
	private:
		void* m_NativeWindow;
	};

	class MouseButtonPressEvent : public MouseEvent
	{
	public:
		MouseButtonPressEvent(void* nativeWindow, MouseButton button, Modifiers modifiers)
			: MouseEvent(nativeWindow), m_Button(button), m_Modifiers(modifiers) {}
		EVENT_TYPE(EventType_MouseButtonPress)
		EVENT_CATEGORIES(EventCategory_Mouse | EventCategory_MouseButton)
#if ENABLE_LOGGING
		virtual operator std::string() const override;
#endif
	public:
		inline MouseButton GetButton() const { return m_Button; }
		inline Modifiers GetModifiers() const { return m_Modifiers; }
	private:
		MouseButton m_Button;
		Modifiers m_Modifiers;
	};

	class MouseButtonReleaseEvent : public MouseEvent
	{
	public:
		MouseButtonReleaseEvent(void* nativeWindow, MouseButton button, Modifiers modifiers)
			: MouseEvent(nativeWindow), m_Button(button), m_Modifiers(modifiers) {}
		EVENT_TYPE(EventType_MouseButtonRelease)
		EVENT_CATEGORIES(EventCategory_Mouse | EventCategory_MouseButton)
#if ENABLE_LOGGING
		virtual operator std::string() const override;
#endif
	public:
		inline MouseButton GetButton() const { return m_Button; }
		inline Modifiers GetModifiers() const { return m_Modifiers; }
	private:
		MouseButton m_Button;
		Modifiers m_Modifiers;
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(void* nativeWindow, float x, float y)
			: MouseEvent(nativeWindow), m_X(x), m_Y(y) {}
		EVENT_TYPE(EventType_MouseMove)
		EVENT_CATEGORIES(EventCategory_Mouse)
#if ENABLE_LOGGING
		virtual operator std::string() const override;
#endif
	public:
		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
	private:
		float m_X;
		float m_Y;
	};

	class MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(void* nativeWindow, float offsetX, float offsetY)
			: MouseEvent(nativeWindow), m_OffsetX(offsetX), m_OffsetY(offsetY) {}
		EVENT_TYPE(EventType_MouseScroll)
		EVENT_CATEGORIES(EventCategory_Mouse)
#if ENABLE_LOGGING
		virtual operator std::string() const override;
#endif
	public:
		inline float GetOffsetX() const { return m_OffsetX; }
		inline float GetOffsetY() const { return m_OffsetY; }
	private:
		float m_OffsetX;
		float m_OffsetY;
	};

	class MouseEnterEvent : public MouseEvent
	{
	public:
		MouseEnterEvent(void* nativeWindow, bool entered)
			: MouseEvent(nativeWindow), m_Entered(entered) {}
		EVENT_TYPE(EventType_MouseEnter)
		EVENT_CATEGORIES(EventCategory_Mouse)
#if ENABLE_LOGGING
		virtual operator std::string() const override;
#endif
	public:
		inline bool HasEntered() const { return m_Entered; }
	private:
		bool m_Entered;
	};
}
