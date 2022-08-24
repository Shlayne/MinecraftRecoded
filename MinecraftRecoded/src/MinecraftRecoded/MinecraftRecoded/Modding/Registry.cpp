#include "MinecraftRecoded/pch.h"
#include "Registry.h"
#include "ModLoader.h"

namespace mcr
{
	struct RegistryData
	{
		// The Registerable's (for now, just Block and Item)
		// hold the memory for the maps' string_views, and they're
		// deleted at the same time, so this is fine.
		std::unordered_map<std::string_view, Block*> blocks;
		std::unordered_map<std::string_view, Item*> items;

		void (* fRegister) (IMod*, Registerable*) = nullptr;
	};

	static RegistryData* s_RegistryData = nullptr;

	template<typename T> requires(std::is_base_of_v<Registerable, T>)
	static void RegisterAll(
#if ENABLE_LOGGING
		const char* typeString,
#endif
		IMod* mod, void (IMod::* getterFunc) (std::vector<T*>&), std::unordered_map<std::string_view, T*>& registryTypes)
	{
		std::vector<T*> registerables;
		(mod->*getterFunc)(registerables);

#if ENABLE_LOGGING
		if (registerables.empty())
			LOG_INFO("No {} to register for mod \"{}\".", typeString, mod->GetID());
		else
			LOG_INFO("Registering {} for mod \"{}\":", typeString, mod->GetID());
#endif

		auto& data = *s_RegistryData;
		for (auto registerable : registerables)
		{
			data.fRegister(mod, registerable);
			registryTypes[registerable->GetFullID()] = registerable;
			LOG_INFO("\t{}", registerable->GetFullID());
		}
	}

	void Registry::Init()
	{
		ASSERT(s_RegistryData == nullptr, "Tried to reinitialize registry.");
		s_RegistryData = new RegistryData();
		s_RegistryData->fRegister = &Registry::Register;

		ModLoader::ForEachMod([](IMod* mod)
		{
			auto& data = *s_RegistryData;
#if ENABLE_LOGGING
			constexpr const char* typeNames[]
			{
				"blocks",
				"items",
			};
	#define TYPE_NAME(index) typeNames[index],
#else
	#define TYPE_NAME(index)
#endif
			RegisterAll<Block>(TYPE_NAME(0) mod, &IMod::GetBlocks, data.blocks);
			RegisterAll<Item>(TYPE_NAME(1) mod, &IMod::GetItems, data.items);
		});
	}

	void Registry::Shutdown()
	{
		ASSERT(s_RegistryData != nullptr, "Tried to reshutdown registry.");
		auto& data = *s_RegistryData;

		for (auto& [fullBlockID, block] : data.blocks)
			delete block;
		for (auto& [fullItemID, item] : data.items)
			delete item;

		delete s_RegistryData;
		s_RegistryData = nullptr;
	}

	const Block* Registry::GetBlock(std::string_view fullBlockID)
	{
		auto& data = *s_RegistryData;
		return data.blocks.contains(fullBlockID) ? data.blocks.at(fullBlockID) : nullptr;
	}

	const Item* Registry::GetItem(std::string_view fullItemID)
	{
		auto& data = *s_RegistryData;
		return data.items.contains(fullItemID) ? data.items.at(fullItemID) : nullptr;
	}

	void Registry::Register(IMod* mod, Registerable* registerable)
	{
		auto& fullID = registerable->fullID;
		fullID.reserve(mod->GetID().size() + 1 + registerable->GetID().size());
		fullID = mod->GetID();
		fullID += ':';
		fullID += registerable->GetID();
	}
}
