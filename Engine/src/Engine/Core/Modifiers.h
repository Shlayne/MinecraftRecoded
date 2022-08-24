#pragma once

#include "Engine/Core/Int.h"

namespace eng
{
	using ModifierFlags_ = uint8;
	enum ModifierFlags : ModifierFlags_
	{
		ModifierFlags_None = 0,
		ModifierFlags_Shift    = 1 << 0,
		ModifierFlags_Control  = 1 << 1,
		ModifierFlags_Alt      = 1 << 2,
		ModifierFlags_Super    = 1 << 3,
		ModifierFlags_CapsLock = 1 << 4,
		ModifierFlags_NumLock  = 1 << 5,

		// Automatically creates a mask of all existing modifier flags.
		ModifierFlags_Last = ModifierFlags_NumLock,
		ModifierFlags_Mask = (ModifierFlags_Last << 1) - 1,
		ModifierFlags_All = ModifierFlags_Mask // Just an alias.
	};

	class Modifiers
	{
	public:
		constexpr Modifiers() = default;
		constexpr Modifiers(ModifierFlags flags) : m_Flags(static_cast<ModifierFlags>(flags & ModifierFlags_Mask)) {}
	public:
		constexpr bool HasAnyOf(ModifierFlags flags) const { return !!(m_Flags & flags); }
		constexpr bool operator==(const Modifiers& modifiers) const { return m_Flags == modifiers.m_Flags; }
		constexpr operator ModifierFlags() const { return m_Flags; }
	private:
		ModifierFlags m_Flags = ModifierFlags_None;
	};
}

#if ENABLE_LOGGING
#include <ostream>

template <class _Elem, class _Traits = std::char_traits<_Elem>>
std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& ostream, eng::Modifiers modifiers)
{
	return ostream << +static_cast<eng::ModifierFlags>(modifiers);
}
#endif
