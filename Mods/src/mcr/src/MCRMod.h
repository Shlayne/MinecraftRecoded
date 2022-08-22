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
		constexpr virtual std::string_view GetID() override { return ID; }
		virtual void GetBlocks(std::vector<IBlock*>& outBlocks) override;
		virtual void GetItems(std::vector<IItem*>& outItems) override;
	};
}
