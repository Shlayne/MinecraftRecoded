include "Dependencies/premake/Custom/solutionitems.lua"

workspace "MinecraftRecoded"
	architecture "x86_64"
	startproject "MinecraftRecoded"

	configurations { "Debug", "Release", "Dist" }

	solutionitems {
		-- Visual Studio
		".editorconfig",

		-- Git
		".gitignore",
		".gitattributes",

		-- Scripts
		"Scripts/GenerateProjects.bat",

		-- Lua Scripts
		"premake5.lua",
		"Dependencies/Dependencies.lua",
		"Dependencies/premake/Custom/solutionitems.lua",
		"Dependencies/premake/Custom/usestdpreproc.lua",
		
		-- Misc
		"README.md"
	}

	flags {
		"MultiProcessorCompile"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/premake/Custom/usestdpreproc.lua"
include "Dependencies/Dependencies.lua"

group "Dependencies/MinecraftRecoded"
	include "MinecraftRecoded/Dependencies/glad-0.1.35/"
	include "MinecraftRecoded/Dependencies/glfw-3.3.8/"
	include "MinecraftRecoded/Dependencies/stb-2.27/"
group ""

-- Add any projects here with 'include "__PROJECT_NAME__"'
include "MinecraftRecoded"
