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
		// A modpack is just a list of required mods (including versions, so you can have multiple mod versions at once),
		//		which mods are being enabled, and what their configs are.
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
									std::vector<IMod*> newMods;
									GetMods(newMods);

									if (!newMods.empty())
									{
										for (auto newMod : newMods)
										{
											bool modIsUnique = true;
											for (auto& mod : s_Mods)
											{
												if (newMod->GetID() == mod.first->GetID())
												{
													modIsUnique = false;
													break;
												}
											}

											if (modIsUnique)
												s_Mods.emplace_back(newMod, hModule);
											else
											{
												LOG_ERROR("Modid \"{}\" already in use found at at \"{}\".", newMod->GetID(), filepath.string());
												ASSERT(false, "TODO: See comment...");
												// TODO:
												// gui will cache all mods upon loading (with refresh button).
												// dependency mods -> MissingDependencyAction.
												// this loader will then not look for all .dll's, but look for
												// the ones in the current modpack. If it can't find all the mods,
												// then it can say so
											}
										}

										#if ENABLE_LOGGING
											LOG_INFO("Mods found at \"{}\":", filepath.string());
											for (auto newMod : newMods)
												LOG_INFO("\t{}", newMod->GetID());
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
				FreeLibrary(hModule = mod.second);
		}
		s_Mods.clear();
	}

	void ModLoader::ForEachMod(const std::function<void(IMod*)>& func)
	{
		for (auto& mod : s_Mods)
			func(mod.first);
	}
}
