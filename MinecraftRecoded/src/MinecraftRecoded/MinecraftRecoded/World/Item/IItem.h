#pragma once

#include "Engine/Core/Int.h"

namespace mcr
{
	class IItem
	{
	public:
		virtual ~IItem() = default;

		virtual uint32 GetMaxStackCount() const = 0;
	};
}
