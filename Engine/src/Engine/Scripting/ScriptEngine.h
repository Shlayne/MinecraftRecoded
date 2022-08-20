#pragma once

namespace eng
{
	class ScriptEngine
	{
	private:
		friend class Application;
		static void Init();
		static void Shutdown();
	private:
		ScriptEngine() = delete;
		ScriptEngine(const ScriptEngine&) = delete;
		ScriptEngine(ScriptEngine&&) = delete;
		ScriptEngine& operator=(const ScriptEngine&) = delete;
		ScriptEngine& operator=(ScriptEngine&&) = delete;
		~ScriptEngine() = delete;
	};
}
