#pragma once

#if SYSTEM_WINDOWS

#include "Engine/Core/Application.h"
#include "Engine/Core/Logger.h"
#include "Engine/Debug/Profiler.h"
#include <filesystem>

bool g_RestartApplication = true;
eng::RendererAPI::API g_NextRendererAPI = eng::RendererAPI::API_None;

namespace eng
{
	extern ApplicationSpecifications CreateApplicationSpecifications(CommandLineArgs args);
	extern Application* CreateApplication(const ApplicationSpecifications& specs);

	int Main(CommandLineArgs args)
	{
		// TODO: change this.
		UNUSED(RendererAPI::SetAPI(RendererAPI::API_OpenGL));

		do
		{
			ApplicationSpecifications specs = CreateApplicationSpecifications(args);

			// Need to set working directory before any profiling, so it has the right directory.
			if (!specs.workingDirectory.empty())
				std::filesystem::current_path(specs.workingDirectory);
#if ENABLE_LOGGING
			Logger::Init();
#endif

			PROFILE_BEGIN_RUNTIME("Init");
			Application* application = CreateApplication(specs);
			PROFILE_END_RUNTIME();

			PROFILE_BEGIN_RUNTIME("Run");
			application->Run();
			PROFILE_END_RUNTIME();

			PROFILE_BEGIN_RUNTIME("Shutdown");
			delete application;
			PROFILE_END_RUNTIME();

			if (!RendererAPI::SetAPI(g_NextRendererAPI))
			{
				LOG_CORE_WARN("Could not set Renderer API to {}. Defaulting to old Renderer API {}", +g_NextRendererAPI, +RendererAPI::GetAPI());
				g_NextRendererAPI = RendererAPI::GetAPI();
			}
		}
		while (g_RestartApplication);

		return 0;
	}
}

#if CONFIG_DIST
#include <Windows.h>

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNUSED(hInst, hInstPrev, lpCmdLine, nCmdShow);
	return eng::Main({ __argc, __argv });
}
#else // !CONFIG_DIST
int main(int argc, char** argv)
{
	return eng::Main({ argc, argv });
}
#endif // CONFIG_DIST

#endif // SYSTEM_WINDOWS
