#include "MinecraftRecoded/pch.h"
#include <Engine/Core/EntryPoint.h>

namespace eng
{
	Application* CreateApplication(CommandLineArgs args)
	{
		Application* pApplication = new Application(args);

		WindowSpecifications windowSpecs;
		windowSpecs.width = 1600;
		windowSpecs.height = 900;
		windowSpecs.title = "Minecraft Recoded";
		UNUSED(pApplication->OpenWindow(windowSpecs));

		return pApplication;
	}
}
