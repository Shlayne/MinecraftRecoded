#include "MinecraftRecoded/pch.h"
#include <Engine/Core/EntryPoint.h>
#include "Layers/WorldLayer.h"

namespace eng
{
	ApplicationSpecifications CreateApplicationSpecifications(CommandLineArgs args)
	{
		ApplicationSpecifications specs;
		specs.args = args;
		specs.workingDirectory = "../Mods/";

		// Window Specs
		auto& windowSpecs = specs.windowSpecs;
		windowSpecs.width = 1600;
		windowSpecs.height = 900;
		windowSpecs.title = "Minecraft Recoded";

		return specs;
	}

	Application* CreateApplication(const ApplicationSpecifications& specs)
	{
		Application* application = new Application(specs);

		application->PushLayer(new mcr::WorldLayer());

		return application;
	}
}
