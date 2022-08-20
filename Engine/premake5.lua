project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	pchheader "Engine/pch.h"
	pchsource "src/Engine/pch.cpp"

	files {
		"src/Engine/**.h",
		"src/Engine/**.cpp",
		"src/Engine/**.inl",
		"src/Engine.h",
		"src/Platform/RendererAPI/**.h",
		"src/Platform/RendererAPI/**.cpp",
		"src/Platform/RendererAPI/**.inl",
	}

	includedirs {
		-- Add any project source directories here.
		"src",
		-- "%{wks.location}/__PROJECT_NAME__/src",

		-- Add any dependency includes here.
		"%{IncludeDir.gcem}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.spdlog}",
	}

	-- Add any links dependency libs via their project names here.
	links {
		"glad",
		"stb",

		"%{Library.mono}",
	}

	defines ("SCRIPT_CORE_ASSEMBLY_FILEPATH=\"Resources/Scripts/bin/" .. OutputDir .. "/ScriptCore.dll\"")

	filter "system:windows"
		systemversion "latest"
		usestdpreproc "On"
		buildoptions "/wd5105" -- Until Microsoft updates Windows 10 to not have terrible code (aka never), this must be here to prevent a warning.

		defines "SYSTEM_WINDOWS"

		includedirs {
			"%{IncludeDir.glfw}",
		}

		links {
			"glfw",
			"%{Library.winsock}",
			"%{Library.winmm}",
			"%{Library.winver}",
			"%{Library.winbcrypt}",
		}

		files {
			"src/Platform/System/Windows/**.h",
			"src/Platform/System/Windows/**.cpp",
			"src/Platform/System/Windows/**.inl",
		}

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

		defines {
			"CONFIG_DEBUG",

			"ENABLE_PROFILE",
			"ENABLE_ASSERTS",
			"ENABLE_STATS",
			"ENABLE_LOGGING",
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

		defines {
			"CONFIG_RELEASE",

			"ENABLE_STATS",
			"ENABLE_LOGGING"
		}

		excludes {
			"src/Engine/Debug/**.h",
			"src/Engine/Debug/**.cpp",
			"src/Engine/Debug/**.inl",
		}

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full"
		symbols "Off"

		defines {
			"CONFIG_DIST"
		}

		excludes {
			"src/Engine/Debug/**.h",
			"src/Engine/Debug/**.cpp",
			"src/Engine/Debug/**.inl",
			"src/Engine/Events/WindowEvents.cpp",
			"src/Engine/Events/KeyEvents.cpp",
			"src/Engine/Events/MouseEvents.cpp",
			"src/Engine/Events/DeviceEvents.cpp",
		}
