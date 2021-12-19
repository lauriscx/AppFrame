#include "Application.h"
#include "Asserts.h"

#include "Application/Events/AppEvents.h"

#include <functional>

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application() : EventHandler("Application") {
	/* Important init data only in run function */

	/* Here subscribe crucial events for application */
	SubscribeToEvent(WindowCloses::Type());
	SubscribeToEvent(WindowResize::Type());

	SetOnFatal	(std::bind(&Application::OnFatal,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnError	(std::bind(&Application::OnError,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnWarning(std::bind(&Application::OnWarning, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnInfo	(std::bind(&Application::OnInfo,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnTrace	(std::bind(&Application::OnTrace,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnDebug	(std::bind(&Application::OnDebug,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void Engine::Application::Run() {
	m_Context = new AppContext(m_Config);
	m_Device = new Device();

	for (auto module : m_Modules) {
		module.second->OnInit(m_Context);
	}
	for (auto module : m_Modules) {
		module.second->OnStart();
	}
}

void Engine::Application::OnEarlyUpdate() {
	m_Timer.Start();
	ModuleRegistry::OnEarlyUpdate(m_Timer.Elapsed());
}
void Engine::Application::OnUpdate	() {
	ModuleRegistry::OnMiddleUpdate(m_Timer.Elapsed());
}
void Engine::Application::OnLateUpdate() {
	ModuleRegistry::OnLateUpdate(m_Timer.Elapsed());
	m_Timer.Stop();
}

bool Engine::Application::OnEvent	(BasicEvent & event) {
	for (auto module : m_Modules) {
		module.second->OnAppEvent(&event);
	}
	return false;
}
bool Engine::Application::OnInput	(int x, int y, int action, int key) {
	for (auto module : m_Modules) {
		module.second->OnAppInput(x, y, action, key);
	}
	return true;
}

AppConfig		* Engine::Application::GetConfig	() {
	return m_Config;
}
AppContext		* Engine::Application::GetContext	() {
	return m_Context;
}
Engine::Device	* Engine::Application::GetDevice	() {
	return m_Device;
}

void Engine::Application::Stop	() {
	for (auto module : m_Modules) {
		module.second->OnStop();
	}
	delete m_Context;
}

void Engine::Application::AddStatus(Status status) {
	m_Status = (Status)(m_Status | status);
}
void Engine::Application::RemoveStatus(Status status) {
	m_Status = (Status)(m_Status & ~status);
}
bool Engine::Application::IsStatus(Status status) {
	return m_Status & status;
}
Engine::Application::Status Engine::Application::GetStatus() {
	return m_Status;
}

Engine::Application::~Application() {}

/* these callbacks are used for module system. If happen some event/log then will be called these functions */
void Engine::Application::OnFatal	(const char * module, const char * file, unsigned int line, const char * msg) {}
void Engine::Application::OnError	(const char * module, const char * file, unsigned int line, const char * msg) {}
void Engine::Application::OnWarning	(const char * module, const char * file, unsigned int line, const char * msg) {}
void Engine::Application::OnInfo	(const char * module, const char * file, unsigned int line, const char * msg) {}
void Engine::Application::OnTrace	(const char * module, const char * file, unsigned int line, const char * msg) {}
void Engine::Application::OnDebug	(const char * module, const char * file, unsigned int line, const char * msg) {}