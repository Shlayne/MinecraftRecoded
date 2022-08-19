#pragma once

#include <functional>
#if ENABLE_LOGGING
	#include <string>
#endif

namespace eng
{
	using EventType_ = uint8;
	enum EventType : EventType_
	{
		EventType_WindowClose,
		EventType_WindowResize,
		EventType_WindowFramebufferResize,
		EventType_WindowMove,
		EventType_WindowFocus,
		EventType_WindowMinimize,
		EventType_WindowMaximize,
		EventType_WindowPathDrop,
		EventType_WindowContentScale,
		EventType_WindowRefresh,
		
		EventType_KeyPress,
		EventType_KeyRepeat,
		EventType_KeyRelease,
		EventType_CharType,
		
		EventType_MouseButtonPress,
		EventType_MouseButtonRelease,
		EventType_MouseMove,
		EventType_MouseScroll,
		EventType_MouseEnter,
		
		EventType_JoystickConnect,
		EventType_MonitorConnect
	};

	using EventCategory_ = uint8;
	enum EventCategory : EventCategory_
	{
		EventCategory_None = 0,
		EventCategory_Window      = 1 << 0,
		EventCategory_Keyboard    = 1 << 1,
		EventCategory_Mouse       = 1 << 2,
		EventCategory_MouseButton = 1 << 3,
		EventCategory_Device      = 1 << 4
	};

#define EVENT_TYPE(type) \
		static constexpr EventType GetStaticType() { return (type); } \
		inline virtual EventType GetType() const override { return GetStaticType(); }

#define EVENT_CATEGORIES(categories) \
		inline virtual EventCategory GetCategories() const override { return static_cast<EventCategory>(categories); }

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategories() const = 0;
		inline bool IsInCategories(EventCategory categories) const;
#if ENABLE_LOGGING
	public:
		virtual operator std::string() const = 0;
#endif
	public:
		template<typename C, typename E>
		inline void Dispatch(C* object, void(C::*fCallback)(E&));
		template<typename E>
		inline void Dispatch(void(*fCallback)(E&));
	public:
		inline bool IsHandled() const;
		inline void Handle();
	private:
		bool m_Handled = false;
	};

	using EventCallback = std::function<void(Event&)>;
}

#include "Event.inl"
