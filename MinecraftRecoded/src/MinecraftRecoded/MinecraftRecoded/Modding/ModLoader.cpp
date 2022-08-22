#include "MinecraftRecoded/pch.h"
#include "ModLoader.h"
#include <filesystem>

// TODO: for now, this is windows only because of LoadLibraryW, GetProcAddress, FreeLibrary, and HMODULE.
// It's fairly simple to make this cross-platform, so if/when it comes to that, it won't take long.

namespace mcr
{
	using FGetMods = void (*) (std::vector<mcr::IMod*>&);

	static std::vector<std::pair<mcr::IMod*, HMODULE>> s_Mods;

	void ModLoader::Load()
	{
		// TODO:
		// A mod profile is just a vector of which mods are being enabled, and what their configs are.
		// At title screen, there's a modding button
		//	gui allows for creating, deleting, copying, renaming, and editing of mod profiles.

		std::error_code error;
		for (auto& entry : std::filesystem::directory_iterator(MODDING_BIN_DIR, error))
		{
			if (entry.is_directory(error))
			{
				for (auto& entry : std::filesystem::directory_iterator(entry, error))
				{
					if (entry.is_regular_file(error))
					{
						auto& filepath = entry.path();
						auto& filepathString = filepath.native();
						if (filepathString.ends_with(L".dll"))
						{
							LOG_INFO("Potential mods found at \"{}\".", filepath.string());

							HMODULE hModule = LoadLibraryW(filepathString.c_str());
							if (hModule != NULL)
							{
								auto GetMods = (FGetMods)GetProcAddress(hModule, "GetMods");
								if (GetMods != NULL)
								{
									std::vector<IMod*> mods;
									GetMods(mods);

									if (!mods.empty())
									{
										for (auto mod : mods)
											s_Mods.emplace_back(mod, hModule);

										#if ENABLE_LOGGING
											LOG_INFO("Mods found at \"{}\":", filepath.string());
											for (auto mod : mods)
												LOG_INFO("\t{}", mod->GetID());
										#endif
									}
									else
										LOG_WARN("Mods at \"{}\" did not have any mods.", filepath.string());
								}
								else
								{
									LOG_WARN("Mods at \"{}\" did not have GetMods function. Error Code: {}", filepath.string(), GetLastError());
									FreeLibrary(hModule);
								}
							}
							else
								LOG_WARN("Failed to load mods at \"{}\". Error Code: {}", filepath.string(), GetLastError());
						}
					}
				}
			}
		}
	}

	void ModLoader::Unload()
	{
		HMODULE hModule = NULL;
		for (auto& mod : s_Mods)
		{
			delete mod.first;
			if (hModule != mod.second)
			{
				hModule = mod.second;
				FreeLibrary(hModule);
			}
		}
		s_Mods.clear();
	}

	void ModLoader::ForEachMod(const std::function<void(IMod*)>& func)
	{
		for (auto& mod : s_Mods)
			func(mod.first);
	}
}
