#include "MCRMod.h"
#include "Blocks/Blocks.h"

namespace mcr
{
	void MCRMod::GetBlocks(std::vector<Block*>& outBlocks)
	{
		outBlocks.reserve(2);
		outBlocks.push_back(new AirBlock());
		outBlocks.push_back(new StoneBlock());
	}

	void MCRMod::GetItems(std::vector<Item*>& outItems)
	{

	}
}

DLL_EXPORT void GetMods(std::vector<mcr::IMod*>& outMods)
{
	outMods.reserve(1);
	outMods.push_back(new mcr::MCRMod());
}
