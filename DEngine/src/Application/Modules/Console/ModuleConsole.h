#pragma once
#include "Application/Modules/Module.h"
#include "Core/Core.h"

#define SPDLOG_LEVEL_NAMES { "[ trace ]", "[ debug ]", "[ info ]", "[warning]", "[ error ]", "[ fatal ]", "[     ]" }//Defining names for logging
#include <spdlog/spdlog.h>

namespace Engine {
	class ModuleConsole : public Module {
	public:
		enum level {
			trace,
			debug,
			info,
			warn,
			error,
			fatal,
			off,
			count
		};
	public:
		ModuleConsole();

		void SetLoggingLevel(ModuleConsole::level level);

		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		virtual void OnAppInput(int x, int y, int action, int key) override;
		virtual void OnAppEvent(BasicEvent* event) override;
		virtual void OnStop() override;

		void Info	(const char* module, const char* message);
		void Trace	(const char* module, const char* message);
		void Debug	(const char* module, const char* message);
		void Warn	(const char* module, const char* message);
		void Error	(const char* module, const char* message);
		void Fatal	(const char* module, const char* message);

		virtual ~ModuleConsole();
	private:
		std::shared_ptr<spdlog::logger> m_Logger;
	};
}