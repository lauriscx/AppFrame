#include "ModuleConsole.h"
#include <spdlog/sinks/stdout_color_sinks.h>

Engine::ModuleConsole::ModuleConsole() {
	spdlog::set_pattern("%^[%H:%M:%S] %l [thread %t] %v%$");
	m_Logger = spdlog::stdout_color_mt("APP FRAME");
	m_Logger->set_level(spdlog::level::trace);
}

void Engine::ModuleConsole::SetLoggingLevel(ModuleConsole::level level) {
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

void Engine::ModuleConsole::OnStart			() {
	Info(quote(ModuleConsole), "Started");
}
void Engine::ModuleConsole::OnEarlyUpdate	(float deltaTime) {}
void Engine::ModuleConsole::OnUpdate		(float deltaTime) {}
void Engine::ModuleConsole::OnLateUpdate	(float deltaTime) {}
void Engine::ModuleConsole::OnAppInput		(int x, int y, int action, int key) {}
void Engine::ModuleConsole::OnAppEvent		(BasicEvent * event) {}
void Engine::ModuleConsole::OnStop			() {}

void Engine::ModuleConsole::Info	(const char * module, const char * message) {
	m_Logger->info("[{}] {}", module, message);
}
void Engine::ModuleConsole::Trace	(const char * module, const char * message) {
	m_Logger->trace("[{}] {}", module, message);
}
void Engine::ModuleConsole::Debug	(const char * module, const char * message) {
	m_Logger->debug("[{}] {}", module, message);
}
void Engine::ModuleConsole::Warn	(const char * module, const char * message) {
	m_Logger->warn("[{}] {}", module, message);
}
void Engine::ModuleConsole::Error	(const char * module, const char * message) {
	m_Logger->error("[{}] {}", module, message);
}
void Engine::ModuleConsole::Fatal	(const char * module, const char * message) {
	m_Logger->critical("[{}] {}", module, message);
}

int Engine::ModuleConsole::ID() {
	return 2;
}

Engine::ModuleConsole::~ModuleConsole() {}