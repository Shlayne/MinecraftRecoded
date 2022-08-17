#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/CommandLineArgs.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/LayerStack.h"
#include "Engine/Core/Window.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Rendering/RendererAPI.h"

namespace eng
{
	struct ApplicationSpecifications
	{
		CommandLineArgs args;
		std::string_view workingDirectory;
		WindowSpecifications windowSpecs;
	};

	class Application
	{
	public:
		static Application& Get();
		inline Window& GetWindow() { return *m_sWindow; }
	public:
		void Restart(RendererAPI::API nextRendererAPI = RendererAPI::GetAPI());
		void Close();
	public:
		void PushLayer(Layer* pLayer);
		void PushOverlay(Layer* pOverlay);
		Layer* PopLayer();
		Layer* PopOverlay();
	private:
		void OnEvent(Event& rEvent);
		void OnWindowCloseEvent(WindowCloseEvent& rEvent);
		void OnWindowResizeEvent(WindowResizeEvent& rEvent);
		void OnWindowMinimizeEvent(WindowMinimizeEvent& rEvent);
	private:
		friend class Input;
		inline Input& GetInput() { return *m_sInput; }
	private:
		Scope<Input> m_sInput;
		Scope<Window> m_sWindow;
		LayerStack m_LayerStack;
	private:
		bool m_Running : 1 = false;
		bool m_Rendering : 1 = false;
	private:
		friend int Main(CommandLineArgs args);
		void Run();
	protected:
		friend Application* CreateApplication(CommandLineArgs args);
		Application(const ApplicationSpecifications& crSpecs);
		virtual ~Application();
	private:
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;
	};
}
