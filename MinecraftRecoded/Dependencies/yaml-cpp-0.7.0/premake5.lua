project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp",
		"include/**.h",
		"src/contrib/yaml-cpp.natvis"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Profile"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "configurations:Debug"
		runtime "Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full"
		symbols "Off"
