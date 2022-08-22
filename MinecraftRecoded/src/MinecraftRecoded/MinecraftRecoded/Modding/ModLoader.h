#pragma once

#include "IMod.h"
#include <functional>

namespace mcr
{
	class ModLoader
	{
	public:
		static void Load();
		static void Unload();
	public:
		static void ForEachMod(const std::function<void(IMod*)>& func);
	private:
		ModLoader() = delete;
		~ModLoader() = delete;
		ModLoader(const ModLoader&) = delete;
		ModLoader(ModLoader&&) = delete;
		ModLoader& operator=(const ModLoader&) = delete;
		ModLoader& operator=(ModLoader&&) = delete;
	};
}
