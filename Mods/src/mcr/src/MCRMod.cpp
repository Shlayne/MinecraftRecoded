#include "MCRMod.h"
#include "Blocks/TestBlock.h"

namespace mcr
{
	void MCRMod::GetBlocks(std::vector<IBlock*>& outBlocks)
	{
		outBlocks.push_back(new TestBlock());
	}

	void MCRMod::GetItems(std::vector<IItem*>& outItems)
	{

	}
}

DLL_EXPORT void GetMods(std::vector<mcr::IMod*>& outMods)
{
	outMods.push_back(new mcr::MCRMod());
}
