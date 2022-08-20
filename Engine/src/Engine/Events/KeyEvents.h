#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Core/Keycodes.h"
#include "Engine/Core/Modifiers.h"

namespace eng
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(void* nativeWindow)
			: m_NativeWindow(nativeWindow) {}
		EVENT_CATEGORIES(EventCategory_Keyboard)
	public:
		inline void* GetNativeWindow() const { return m_NativeWindow; }
	private:
		void* m_NativeWindow;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(void* nativeWindow, Keycode keycode, Modifiers modifiers)
			: KeyEvent(nativeWindow), m_Keycode(keycode), m_Modifiers(modifiers) {}
		EVENT_TYPE(EventType_KeyPress)
#if ENABLE_LOGGING
	public:
		virtual operator std::string() const override;
#endif
	public:
		inline Keycode GetKeycode() const { return m_Keycode; }
		inline Modifiers GetModifiers() const { return m_Modifiers; }
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class KeyRepeatEvent : public KeyEvent
	{
	public:
		KeyRepeatEvent(void* nativeWindow, Keycode keycode, Modifiers modifiers)
			: KeyEvent(nativeWindow), m_Keycode(keycode), m_Modifiers(modifiers) {}
		EVENT_TYPE(EventType_KeyRepeat)
#if ENABLE_LOGGING
	public:
		virtual operator std::string() const override;
#endif
	public:
		inline Keycode GetKeycode() const { return m_Keycode; }
		inline Modifiers GetModifiers() const { return m_Modifiers; }
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(void* nativeWindow, Keycode keycode, Modifiers modifiers)
			: KeyEvent(nativeWindow), m_Keycode(keycode), m_Modifiers(modifiers) {}
		EVENT_TYPE(EventType_KeyRelease)
#if ENABLE_LOGGING
	public:
		virtual operator std::string() const override;
#endif
	public:
		inline Keycode GetKeycode() const { return m_Keycode; }
		inline Modifiers GetModifiers() const { return m_Modifiers; }
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class CharTypeEvent : public KeyEvent
	{
	public:
		CharTypeEvent(void* nativeWindow, uint32 codepoint)
			: KeyEvent(nativeWindow), m_Codepoint(codepoint) {}
		EVENT_TYPE(EventType_CharType)
#if ENABLE_LOGGING
	public:
		virtual operator std::string() const override;
#endif
	public:
		inline uint32 GetCodepoint() const { return m_Codepoint; }
	private:
		uint32 m_Codepoint;
	};
}
