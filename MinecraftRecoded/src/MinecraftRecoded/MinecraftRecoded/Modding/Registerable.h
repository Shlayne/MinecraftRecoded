#pragma once

#include <string>

namespace mcr
{
	class Registerable
	{
	public:
		constexpr virtual std::string_view GetID() const noexcept = 0;
		constexpr std::string_view GetFullID() const noexcept { return fullID; }
	private:
		friend class Registry;
		std::string fullID;
	};
}
