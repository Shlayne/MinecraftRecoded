IncludeDir = {}
LibraryDir = {}
Library = {}

-- Include Directories
	IncludeDir["gcem"] = "%{wks.location}/Engine/Dependencies/gcem-1.15.0/include/"
	IncludeDir["glad"] = "%{wks.location}/Engine/Dependencies/glad-0.1.35/include/"
	IncludeDir["glfw"] = "%{wks.location}/Engine/Dependencies/glfw-3.3.8/include/"
	IncludeDir["glm"] = "%{wks.location}/Engine/Dependencies/glm-0.9.9.8/include/"
	IncludeDir["mono"] = "%{wks.location}/Engine/Dependencies/mono-6.12.0.184/include/"
	IncludeDir["stb"] = "%{wks.location}/Engine/Dependencies/stb-2.27/include/"
	IncludeDir["spdlog"] = "%{wks.location}/Engine/Dependencies/spdlog-1.10.0/include/"

-- Library Directories
	LibraryDir["mono"] = "%{wks.location}/Engine/Dependencies/mono-6.12.0.184/lib/%{cfg.buildcfg}/"

-- Libraries
	Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

-- Windows Only
	Library["winsock"] = "Ws2_32.lib"
	Library["winmm"] = "Winmm.lib"
	Library["winver"] = "Version.lib"
	Library["winbcrypt"] = "Bcrypt.lib"
