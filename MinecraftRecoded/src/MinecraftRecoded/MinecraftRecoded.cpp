#include "MinecraftRecoded/pch.h"
#include <Engine/Core/EntryPoint.h>

class TestLayer : public eng::Layer
{
public:
	TestLayer()
	{
		LOG_INFO("TestLayer()");
	}

	virtual ~TestLayer()
	{
		LOG_INFO("~TestLayer()");
	}

	virtual void OnAttach() override
	{
		LOG_INFO("OnAttach()");
	}

	virtual void OnDetach() override
	{
		LOG_INFO("OnDetach()");
	}

	virtual void OnUpdate(eng::Timestep timestep) override
	{
		LOG_INFO("OnUpdate({0})", timestep);
	}

	virtual void OnRender() override
	{
		LOG_INFO("OnRender()");
	}

	virtual void OnEvent(eng::Event& rEvent) override
	{
		LOG_INFO("OnEvent({0})", (std::string)rEvent);
	}
};

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

		pApplication->PushLayer(new TestLayer());

		return pApplication;
	}
}
