project "glad"
	filter "system:not windows"
		kind "None"

	filter "system:windows"
		kind "StaticLib"
		language "C"
		cdialect "C17"
		staticruntime "On"

		targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
		objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

		files {
			"include/glad/glad.h",
			"include/KHR/khrplatform.h",
			"src/glad.c"
		}

		includedirs {
			"include"
		}

		filter "system:windows"
			systemversion "latest"
			buildoptions "/wd5105" -- Until Microsoft updates Windows 10 to not have terrible code (aka never), this must be here to prevent a warning.

		filter { "system:windows", "configurations:Profile" }
			runtime "Debug"
			optimize "Off"
			symbols "On"

		filter { "system:windows", "configurations:Debug" }
			runtime "Debug"
			optimize "Debug"
			symbols "Full"

		filter { "system:windows", "configurations:Release" }
			runtime "Release"
			optimize "On"
			symbols "On"

		filter { "system:windows", "configurations:Dist" }
			runtime "Release"
			optimize "Full"
			symbols "Off"
