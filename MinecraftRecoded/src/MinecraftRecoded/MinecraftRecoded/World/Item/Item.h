#pragma once

#include <Engine/Core/Int.h>
#include "Modding/Registerable.h"

namespace mcr
{
	class Item : public Registerable
	{
	public:
		virtual ~Item() = default;

		virtual uint32 GetMaxStackCount() const = 0;
	};
}
