#include "MinecraftRecoded/pch.h"
#include <Engine/Core/EntryPoint.h>
#include "Layers/WorldLayer.h"

namespace eng
{
	Application* CreateApplication(CommandLineArgs args)
	{
		ApplicationSpecifications applicationSpecs;
		applicationSpecs.args = args;

		// Window Specs
		auto& windowSpecs = applicationSpecs.windowSpecs;
		windowSpecs.width = 1600;
		windowSpecs.height = 900;
		windowSpecs.title = "Minecraft Recoded";

		Application* pApplication = new Application(applicationSpecs);

		pApplication->PushLayer(new mcr::WorldLayer());

		return pApplication;
	}
}
