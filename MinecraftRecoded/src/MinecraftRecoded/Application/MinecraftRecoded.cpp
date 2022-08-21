#include "MinecraftRecoded/pch.h"
#include <Engine/Core/EntryPoint.h>
#include "Layers/WorldLayer.h"

namespace eng
{
	Application* CreateApplication(CommandLineArgs args)
	{
		ApplicationSpecifications applicationSpecs;
		applicationSpecs.args = args;
		applicationSpecs.workingDirectory = "./MinecraftRecoded/";

		// Window Specs
		auto& windowSpecs = applicationSpecs.windowSpecs;
		windowSpecs.width = 1600;
		windowSpecs.height = 900;
		windowSpecs.title = "Minecraft Recoded";

		Application* application = new Application(applicationSpecs);

		application->PushLayer(new mcr::WorldLayer());

		return application;
	}
}
