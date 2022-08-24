#include "MCRMod.h"
#include "Blocks/Blocks.h"

namespace mcr
{
	ModVersion MCRMod::GetVersion() const
	{
		return { 0, 12, 1 };
	}

	void MCRMod::GetDependencies(std::vector<ModDependency>& outDependencies)
	{
		// Example:
		//outDependencies.reserve(1);
		//outDependencies.push_back({ "mcr2", { { 1, 0, 0 }, { 2, 0, 0 }, false }, ModDependencyType_HardRequired });
	}

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
