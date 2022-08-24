project "MinecraftRecoded"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	pchheader "MinecraftRecoded/pch.h"
	pchsource "src/MinecraftRecoded/pch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.inl"
	}

	includedirs {
		-- Add any project source directories here.
		"src",
		"src/MinecraftRecoded/MinecraftRecoded",
		"%{wks.location}/Engine/src",

		-- Add any dependency includes here.
		"%{IncludeDir.gcem}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.siv}",
		"%{IncludeDir.spdlog}",
	}

	defines {
		"MODDING_BIN_DIR=\"bin/" .. OutputDir .. "\""
	}

	-- Add any links dependency libs via their project names here.
	links {
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"
		usestdpreproc "On"
		buildoptions "/wd5105" -- Until Microsoft updates Windows 10 to not have terrible code (aka never), this must be here to prevent a warning.
		defines "SYSTEM_WINDOWS"

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

		kind "WindowedApp"
