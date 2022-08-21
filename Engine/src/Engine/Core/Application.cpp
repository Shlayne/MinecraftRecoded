#include "Engine/pch.h"
#include "Engine/Core/Application.h"
#include "Engine/Rendering/Renderer.h"
#include <filesystem>

extern bool g_RestartApplication;
extern eng::RendererAPI::API g_NextRendererAPI;

namespace eng
{
	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpecifications& specs)
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(s_Application == nullptr, "Attempted to recreate Application!");
		s_Application = this;

		if (!specs.workingDirectory.empty())
			std::filesystem::current_path(specs.workingDirectory);

		m_Input = Input::CreateScope(BIND_FUNC(OnEvent));
		m_Window = Window::CreateScope(specs.windowSpecs);
		Renderer::Init();
	}

	Application::~Application()
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(s_Application != nullptr, "Attempted to redestroy Application!");

		// If layers aren't deleted by now, assume ownership and delete them.
		for (auto& layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}

		Renderer::Shutdown();
		DestroyScope(m_Window);
		DestroyScope(m_Input);

		s_Application = nullptr;
	}

	Application& Application::Get()
	{
		CORE_ASSERT(s_Application != nullptr, "Attempted to get the application before it was created!");
		return *s_Application;
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

	void Application::PushLayer(Layer* layer)
	{
		CORE_ASSERT(layer != nullptr, "Layer was nullptr.");

		layer->OnAttach();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		CORE_ASSERT(overlay != nullptr, "Overlay was nullptr.");

		overlay->OnAttach();
		m_LayerStack.PushOverlay(overlay);
	}

	Layer* Application::PopLayer()
	{
		Layer* layer = m_LayerStack.PopLayer();
		if (layer != nullptr)
			layer->OnDetach();
#if ENABLE_LOGGING
		else
			LOG_CORE_WARN("Popping layer when there is no layer to pop. Potential push/pop layer/overlay imbalance.");
#endif
		return layer;
	}

	Layer* Application::PopOverlay()
	{
		Layer* overlay = m_LayerStack.PopOverlay();
		if (overlay != nullptr)
			overlay->OnDetach();
#if ENABLE_LOGGING
		else
			LOG_CORE_WARN("Popping overlay when there is no overlay to pop. Potential push/pop layer/overlay imbalance.");
#endif
		return overlay;
	}

	void Application::OnEvent(Event& event)
	{
		PROFILE_FUNCTION();

		event.Dispatch(this, &Application::OnWindowMinimizeEvent);
		event.Dispatch(this, &Application::OnWindowResizeEvent);

		for (auto it = m_LayerStack.rbegin(); !event.IsHandled() && it != m_LayerStack.rend(); ++it)
		{
			Layer& layer = **it;
			if (layer.IsEnabled())
				layer.OnEvent(event);
		}

		// Dispatch this last, in case a layer handled the close event.
		event.Dispatch(this, &Application::OnWindowCloseEvent);
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		Close();
	}

	void Application::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		m_Rendering = event.GetWidth() > 0 && event.GetHeight() > 0 && !m_Window->IsMinimized();
	}

	void Application::OnWindowMinimizeEvent(WindowMinimizeEvent& event)
	{
		m_Rendering = !event.IsMinimized() && m_Window->GetWidth() > 0 && m_Window->GetHeight() > 0;
	}

	void Application::Run()
	{
		CORE_ASSERT(m_Running == false, "Cannot run the application while it is already running!");
		m_Running = true;
		m_Rendering = true;

		// Send resize events to resize any cameras/framebuffers/etc.
		{
			PROFILE_SCOPE("Application::Run -> Initial Resize Events");
			Window& window = GetWindow();
			WindowResizeEvent wre(window.GetNativeWindow(), window.GetWidth(), window.GetHeight());
			OnEvent(wre);
			WindowFramebufferResizeEvent wfre(window.GetNativeWindow(), window.GetFramebufferWidth(), window.GetFramebufferHeight());
			OnEvent(wfre);
		}

		Input& input = *m_Input;
		while (m_Running)
		{
			PROFILE_SCOPE("Application::Run -> while(m_Running)");

			Timestep timestep = input.GetElapsedTime();

			// Update
			{
				PROFILE_SCOPE("Application::Run -> Update");
				for (auto& layer : m_LayerStack)
					if (layer->IsEnabled())
						layer->OnUpdate(timestep);
			}

			// Render
			if (m_Rendering)
			{
				PROFILE_SCOPE("Application::Run -> Render");

				for (auto& layer : m_LayerStack)
					if (layer->IsEnabled())
						layer->OnRender();
				m_Window->GetContext().SwapBuffers();
			}

			input.PollEvents();
		}
	}
}
