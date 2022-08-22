#pragma once

#include "World/Chunk/Block/IBlock.h"
#include "World/Item/IItem.h"
#include <string_view>
#include <vector>

namespace mcr
{
	class IMod
	{
	public:
		virtual ~IMod() = default;

		virtual std::string_view GetID() = 0;
		virtual void GetBlocks(std::vector<IBlock*>& outBlocks) = 0;
		virtual void GetItems(std::vector<IItem*>& outItems) = 0;
	};
}
