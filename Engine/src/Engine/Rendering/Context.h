#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Timestep.h"

namespace eng
{
	class Context
	{
	public:
		static Scope<Context> CreateScope(void* nativeWindow);
		virtual ~Context() = default;
	public:
		virtual void SwapBuffers() = 0;
		virtual void MakeCurrent() = 0;
	};

	void WithContext(void* nativeWindow, const std::function<void()>& work);
	void RemoveCurrentContext();
}
