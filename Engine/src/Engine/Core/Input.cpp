#include "Engine/pch.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Application.h"
#if SYSTEM_WINDOWS
	#include "Platform/System/Windows/WindowsInput.h"
#endif

namespace eng
{
	Scope<Input> Input::CreateScope(EventCallback&& eventCallback)
	{
#if SYSTEM_WINDOWS
		return eng::CreateScope<WindowsInput>(std::move(eventCallback));
#endif
	}

	Input& Input::Get()
	{
		return Application::Get().GetInput();
	}
}
