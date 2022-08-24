#pragma once

#include <type_traits>

namespace mcr
{
	// Wrapper for primitive types that allows inheriters to call their own functions via its operators.
	// WARNING: Does not and cannot call said functions if this type is punned to something else.
	template<typename T> requires(std::is_arithmetic_v<T>)
	struct PrimitiveWrapper
	{
	public:
		using Value = T;
	public:
		constexpr PrimitiveWrapper() noexcept = default;
		template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
		constexpr PrimitiveWrapper(T2 value) noexcept : m_Value(static_cast<Value>(value)) {}

	// These being virtual would inflict the vtable performance hit.
	// Not to mention that the middle section can't be virtual 'cause of the templates.
	// Instead, just copy these definitions to your subclass and implement them.
	// They don't need to be constexpr nor noexcept.

	//public:
	//	constexpr Value operator+(Value value) const noexcept;
	//	constexpr PrimitiveWrapper& operator+=(Value value) noexcept;
	//	constexpr Value operator-(Value value) const noexcept;
	//	constexpr PrimitiveWrapper& operator-=(Value value) noexcept;
	//	constexpr Value operator*(Value value) const noexcept;
	//	constexpr PrimitiveWrapper& operator*=(Value value) noexcept;
	//	constexpr Value operator/(Value value) const noexcept;
	//	constexpr PrimitiveWrapper& operator/=(Value value) noexcept;
	//public:
	//	template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
	//	constexpr Value operator+(T2 value) const noexcept;
	//	template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
	//	constexpr Value operator-(T2 value) const noexcept;
	//	template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
	//	constexpr Value operator*(T2 value) const noexcept;
	//	template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
	//	constexpr Value operator/(T2 value) const noexcept;
	//public:
	//	constexpr Value operator++(int) noexcept;
	//	constexpr PrimitiveWrapper& operator++() noexcept;
	//	constexpr Value operator--(int) noexcept;
	//	constexpr PrimitiveWrapper& operator--() noexcept;
	public:
		constexpr Value operator+() const noexcept { return +m_Value; }
		constexpr Value operator-() const noexcept { return -m_Value; }
	public:
		constexpr operator Value() const noexcept { return m_Value; }
		constexpr explicit operator bool() const noexcept { return m_Value != static_cast<Value>(0); }
		constexpr bool operator!() const noexcept { return m_Value == static_cast<Value>(0); }
	public:
		constexpr Value* operator&() noexcept { return &m_Value; }
		constexpr const Value* operator&() const noexcept { return &m_Value; }
	protected:
		Value m_Value = static_cast<Value>(0);
	};
}
