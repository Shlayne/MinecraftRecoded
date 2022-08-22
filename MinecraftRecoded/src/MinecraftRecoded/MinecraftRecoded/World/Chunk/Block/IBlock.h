#pragma once

namespace mcr
{
	class IBlock
	{
	public:
		virtual ~IBlock() = default;

		virtual bool IsSolid() const = 0;
	};
}
