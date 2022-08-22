#pragma once

#include "World/Chunk/Block/IBlock.h"

namespace mcr
{
	class TestBlock : public IBlock
	{
	public:
		constexpr virtual bool IsSolid() const override { return true; }
	};
}
