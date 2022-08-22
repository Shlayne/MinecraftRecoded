#pragma once

#include "Modding/IMod.h"
#include "Modding/Registerable.h"
#include "World/Chunk/Block/Block.h"
#include "World/Item/Item.h"

namespace mcr
{
	class Registry
	{
	public:
		static void Init();
		static void Shutdown();
	public:
		static Block* GetBlock(std::string_view fullBlockID);
		static Item* GetItem(std::string_view fullItemID);
	private:
		static void Register(IMod* mod, Registerable* registerable);
	};
}
