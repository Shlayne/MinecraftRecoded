#pragma once

#include <memory>

namespace eng
{
	// Ref
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	inline void DestroyRef(Ref<T>& ref) noexcept
	{
		ref.reset();
	}

	template<typename T, typename T2>
	inline Ref<T> CastRef(const Ref<T2>& ref)
	{
		return std::dynamic_pointer_cast<T, T2>(ref);
	}

	template<typename T, typename T2>
	inline Ref<T> CastRef(Ref<T2>&& ref)
	{
		return std::dynamic_pointer_cast<T, T2>(std::move(ref));
	}

	// Scope
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	inline void DestroyScope(Scope<T>& scope) noexcept
	{
		scope.reset();
	}
}
