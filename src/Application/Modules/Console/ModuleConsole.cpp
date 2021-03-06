
#define SPDLOG_LEVEL_NAMES { "[ trace ]", "[ debug ]", "[ info ]", "[warning]", "[ error ]", "[ fatal ]", "[     ]" }//Defining names for logging
#include <spdlog/spdlog.h>

#include "ModuleConsole.h"
#include "Application/Events/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

AppFrame::ModuleConsole::ModuleConsole() {
	spdlog::set_pattern("%^[%H:%M:%S] %l [thread %t] %v%$");
	m_Logger = spdlog::stdout_color_mt("APP FRAME");
	m_Logger->set_level(spdlog::level::trace);
}

void AppFrame::ModuleConsole::SetLoggingLevel(ModuleConsole::level level) {
	if (level == level::trace) {
		m_Logger->set_level(spdlog::level::trace);
	} else if(level == level::debug) {
		m_Logger->set_level(spdlog::level::debug);
	}
	else if (level == level::info) {
		m_Logger->set_level(spdlog::level::info);
	}
	else if (level == level::warn) {
		m_Logger->set_level(spdlog::level::warn);
	}
	else if (level == level::error) {
		m_Logger->set_level(spdlog::level::err);
	}
	else if (level == level::fatal) {
		m_Logger->set_level(spdlog::level::critical);
	}
	else if (level == level::off) {
		m_Logger->set_level(spdlog::level::off);
	}
	else {
		m_Logger->set_level(spdlog::level::trace);
	}
}

void AppFrame::ModuleConsole::OnStart			() {
	Info(quote(ModuleConsole), "Started");
}
void AppFrame::ModuleConsole::OnEarlyUpdate	(float deltaTime) {}
void AppFrame::ModuleConsole::OnUpdate		(float deltaTime) {}
void AppFrame::ModuleConsole::OnLateUpdate	(float deltaTime) {}
void AppFrame::ModuleConsole::OnAppInput	(const InputData& input) {}
void AppFrame::ModuleConsole::OnAppEvent	(BasicEvent * event) {
	if (Log* log = Log::Match(event)) {
		if (log->GetLevel() == Log::level::debug) {
			Debug(log->GetModule(), log->GetMsg());
		} else if (log->GetLevel() == Log::level::error) {
			Error(log->GetModule(), log->GetMsg());
		}
		else if (log->GetLevel() == Log::level::fatal) {
			Fatal(log->GetModule(), log->GetMsg());
		}
		else if (log->GetLevel() == Log::level::info) {
			Info(log->GetModule(), log->GetMsg());
		}
		else if (log->GetLevel() == Log::level::trace) {
			Trace(log->GetModule(), log->GetMsg());
		}
		else if (log->GetLevel() == Log::level::warn) {
			Warn(log->GetModule(), log->GetMsg());
		}
	}

}
void AppFrame::ModuleConsole::OnStop			() {}

void AppFrame::ModuleConsole::Info	(const char * module, const char * message) {
	m_Logger->info("[{}] {}", module, message);
}
void AppFrame::ModuleConsole::Trace	(const char * module, const char * message) {
	m_Logger->trace("[{}] {}", module, message);
}
void AppFrame::ModuleConsole::Debug	(const char * module, const char * message) {
	m_Logger->debug("[{}] {}", module, message);
}
void AppFrame::ModuleConsole::Warn	(const char * module, const char * message) {
	m_Logger->warn("[{}] {}", module, message);
}
void AppFrame::ModuleConsole::Error	(const char * module, const char * message) {
	m_Logger->error("[{}] {}", module, message);
}
void AppFrame::ModuleConsole::Fatal	(const char * module, const char * message) {
	m_Logger->critical("[{}] {}", module, message);
}

AppFrame::ModuleConsole::~ModuleConsole() {}