#pragma once

#include <Engine/Core/Int.h>
#include "DLL_EXPORT.h"
#include "Modding/IMod.h"

namespace mcr
{
	class MCRMod : public IMod
	{
	public:
		static constexpr std::string_view ID = "mcr";
	public:
		constexpr virtual std::string_view GetID() const override { return ID; }
		virtual ModVersion GetVersion() const override;
		virtual void GetDependencies(std::vector<ModDependency>& outDependencies) override;
		virtual void GetBlocks(std::vector<Block*>& outBlocks) override;
		virtual void GetItems(std::vector<Item*>& outItems) override;
	};
}
