project "__MOD_NAME__"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	staticruntime "Off"

	targetdir ("%{wks.location}/Mods/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/Mods/bin-int/" .. OutputDir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp",
		"src/**.inl",
		"src/**.ixx"
	}

	includedirs {
		-- Add any project source directories here.
		"src",
		"%{wks.location}/Engine/src",
		"%{wks.location}/MinecraftRecoded/src/MinecraftRecoded/MinecraftRecoded",

		-- Add any dependency includes here.
		"%{IncludeDir.gcem}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",

		-- Misc.
		"%{wks.location}/Mods/src/DLL_EXPORT"
	}

	filter "system:windows"
		systemversion "latest"
		defines "SYSTEM_WINDOWS"

		-- msvc doesn't provide __VA_OPT__ by default; this fixes that.
		usestdpreproc "On"

	filter "configurations:Profile"
		runtime "Debug"
		optimize "Off"
		symbols "On"

		defines {
			"CONFIG_PROFILE",

			"ENABLE_PROFILE",
			"ENABLE_ASSERTS",
			"ENABLE_STATS",
			"ENABLE_LOGGING"
		}

	filter "configurations:Debug"
		runtime "Debug"
		optimize "Debug"
		symbols "Full"
		defines "CONFIG_DEBUG"

		defines {
			"CONFIG_DEBUG",

			"ENABLE_PROFILE",
			"ENABLE_ASSERTS",
			"ENABLE_STATS",
			"ENABLE_LOGGING"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"
		defines "CONFIG_RELEASE"

		defines {
			"CONFIG_RELEASE",

			"ENABLE_STATS",
			"ENABLE_LOGGING"
		}

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full"
		symbols "Off"

		defines {
			"CONFIG_DIST"
		}
