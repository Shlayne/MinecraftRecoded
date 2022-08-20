#include "Engine/pch.h"
#include "Engine/Core/Application.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Scripting/ScriptEngine.h"
#include <filesystem>

extern bool g_RestartApplication;
extern eng::RendererAPI::API g_NextRendererAPI;

namespace eng
{
	static Application* s_pApplication = nullptr;

	Application::Application(const ApplicationSpecifications& crSpecs)
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(s_pApplication == nullptr, "Attempted to recreate Application!");
		s_pApplication = this;

		if (!crSpecs.workingDirectory.empty())
			std::filesystem::current_path(crSpecs.workingDirectory);

		m_sInput = Input::CreateScope(BIND_FUNC(OnEvent));
		m_sWindow = Window::CreateScope(crSpecs.windowSpecs);
		Renderer::Init();
		ScriptEngine::Init();
	}

	Application::~Application()
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(s_pApplication != nullptr, "Attempted to redestroy Application!");

		// If layers aren't deleted by now, assume ownership and delete them.
		for (auto& rLayer : m_LayerStack)
		{
			rLayer->OnDetach();
			delete rLayer;
		}

		ScriptEngine::Shutdown();
		Renderer::Shutdown();
		DestroyScope(m_sWindow);
		DestroyScope(m_sInput);

		s_pApplication = nullptr;
	}

	Application& Application::Get()
	{
		CORE_ASSERT(s_pApplication != nullptr, "Attempted to get the application before it was created!");
		return *s_pApplication;
	}

	void Application::Restart(RendererAPI::API nextRendererAPI)
	{
		g_RestartApplication = true;
		g_NextRendererAPI = nextRendererAPI;
		m_Running = false;
	}

	void Application::Close()
	{
		g_RestartApplication = false;
		g_NextRendererAPI = RendererAPI::GetAPI();
		m_Running = false;
	}

	void Application::PushLayer(Layer* pLayer)
	{
		CORE_ASSERT(pLayer != nullptr, "Layer was nullptr.");

		pLayer->OnAttach();
		m_LayerStack.PushLayer(pLayer);
	}

	void Application::PushOverlay(Layer* pOverlay)
	{
		CORE_ASSERT(pOverlay != nullptr, "Overlay was nullptr.");

		pOverlay->OnAttach();
		m_LayerStack.PushOverlay(pOverlay);
	}

	Layer* Application::PopLayer()
	{
		Layer* pLayer = m_LayerStack.PopLayer();
		if (pLayer != nullptr)
			pLayer->OnDetach();
#if ENABLE_LOGGING
		else
			LOG_CORE_WARN("Popping layer when there is no layer to pop. Potential push/pop layer/overlay imbalance.");
#endif
		return pLayer;
	}

	Layer* Application::PopOverlay()
	{
		Layer* pOverlay = m_LayerStack.PopOverlay();
		if (pOverlay != nullptr)
			pOverlay->OnDetach();
#if ENABLE_LOGGING
		else
			LOG_CORE_WARN("Popping overlay when there is no overlay to pop. Potential push/pop layer/overlay imbalance.");
#endif
		return pOverlay;
	}

	void Application::OnEvent(Event& rEvent)
	{
		PROFILE_FUNCTION();

		rEvent.Dispatch(this, &Application::OnWindowMinimizeEvent);
		rEvent.Dispatch(this, &Application::OnWindowResizeEvent);

		for (auto it = m_LayerStack.rbegin(); !rEvent.IsHandled() && it != m_LayerStack.rend(); ++it)
		{
			Layer& rLayer = **it;
			if (rLayer.IsEnabled())
				rLayer.OnEvent(rEvent);
		}

		// Dispatch this last, in case a layer handled the close event.
		rEvent.Dispatch(this, &Application::OnWindowCloseEvent);
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent& rEvent)
	{
		Close();
	}

	void Application::OnWindowResizeEvent(WindowResizeEvent& rEvent)
	{
		m_Rendering = rEvent.GetWidth() > 0 && rEvent.GetHeight() > 0 && !m_sWindow->IsMinimized();
	}

	void Application::OnWindowMinimizeEvent(WindowMinimizeEvent& rEvent)
	{
		m_Rendering = !rEvent.IsMinimized() && m_sWindow->GetWidth() > 0 && m_sWindow->GetHeight() > 0;
	}

	void Application::Run()
	{
		CORE_ASSERT(m_Running == false, "Cannot run the application while it is already running!");
		m_Running = true;
		m_Rendering = true;

		// Send resize events to resize any cameras/framebuffers/etc.
		{
			PROFILE_SCOPE("Application::Run -> Initial Resize Events");
			Window& rWindow = GetWindow();
			WindowResizeEvent wre(rWindow.GetNativeWindow(), rWindow.GetWidth(), rWindow.GetHeight());
			OnEvent(wre);
			WindowFramebufferResizeEvent wfre(rWindow.GetNativeWindow(), rWindow.GetFramebufferWidth(), rWindow.GetFramebufferHeight());
			OnEvent(wfre);
		}

		Input& rInput = *m_sInput;
		while (m_Running)
		{
			PROFILE_SCOPE("Application::Run -> while(m_Running)");

			Timestep timestep = rInput.GetElapsedTime();

			// Update
			{
				PROFILE_SCOPE("Application::Run -> Update");
				for (auto& rpLayer : m_LayerStack)
					if (rpLayer->IsEnabled())
						rpLayer->OnUpdate(timestep);
			}

			// Render
			if (m_Rendering)
			{
				PROFILE_SCOPE("Application::Run -> Render");

				for (auto& rpLayer : m_LayerStack)
					if (rpLayer->IsEnabled())
						rpLayer->OnRender();
				m_sWindow->GetContext().SwapBuffers();
			}

			rInput.PollEvents();
		}
	}
}
