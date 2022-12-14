#pragma once

#include "World/Chunk/Block/Block.h"
#include "World/Item/Item.h"
#include "ModDependency.h"
#include <string_view>
#include <vector>

namespace mcr
{
	class IMod
	{
	public:
		virtual ~IMod() = default;

		virtual std::string_view GetID() const = 0;
		virtual ModVersion GetVersion() const = 0;
		virtual void GetDependencies(std::vector<ModDependency>& outDependencies) = 0;
		virtual void GetBlocks(std::vector<Block*>& outBlocks) = 0;
		virtual void GetItems(std::vector<Item*>& outItems) = 0;
	};
}
