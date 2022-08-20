project "ScriptCore"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2" -- 4.5 tho?

	targetdir ("%{wks.location}/MinecraftRecoded/Resources/Scripts/bin/" .. OutputDir .. "/")
	objdir ("%{wks.location}/MinecraftRecoded/Resources/Scripts/bin-int/" .. OutputDir .. "/")

	files "Source/**.cs"

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
