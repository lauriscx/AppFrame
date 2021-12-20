#include "Application.h"
#include "Application/Events/AppEvents.h"
#include <functional>
#include "EventSystem/EventManager.h"

AppFrame::Application* AppFrame::Application::s_Instance = nullptr;

AppFrame::Application::Application() : EventHandler("Application") {
	/* Important init data only in run function */
	SetOnFatal	(std::bind(&Application::OnFatal,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnError	(std::bind(&Application::OnError,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnWarning(std::bind(&Application::OnWarning, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnInfo	(std::bind(&Application::OnInfo,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnTrace	(std::bind(&Application::OnTrace,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	SetOnDebug	(std::bind(&Application::OnDebug,	this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void AppFrame::Application::Run() {
	m_Context = new AppContext(m_Config);
	m_Device = new Device();

	for (auto module : m_Modules) {
		module.second->OnInit(m_Context);
	}
	for (auto module : m_Modules) {
		module.second->OnStart();
	}
}

void AppFrame::Application::OnEarlyUpdate() {
	m_Timer.Start();
	ModuleRegistry::OnEarlyUpdate(m_Timer.Elapsed());
}
void AppFrame::Application::OnUpdate	() {
	ModuleRegistry::OnMiddleUpdate(m_Timer.Elapsed());
}
void AppFrame::Application::OnLateUpdate() {
	ModuleRegistry::OnLateUpdate(m_Timer.Elapsed());
	m_Timer.Stop();
}

bool AppFrame::Application::OnEvent	(BasicEvent & event) {
	for (auto module : m_Modules) {
		module.second->OnAppEvent(&event);
	}
	return false;
}
bool AppFrame::Application::OnInput	(int x, int y, int action, int key) {
	for (auto module : m_Modules) {
		module.second->OnAppInput(x, y, action, key);
	}
	return true;
}

AppFrame::AppConfig		* AppFrame::Application::GetConfig	() {
	return m_Config;
}
AppFrame::AppContext	* AppFrame::Application::GetContext	() {
	return m_Context;
}
AppFrame::Device	* AppFrame::Application::GetDevice	() {
	return m_Device;
}

void AppFrame::Application::Stop	() {
	for (auto module : m_Modules) {
		module.second->OnStop();
	}
	delete m_Context;
}

void AppFrame::Application::AddStatus(Status status) {
	m_Status = (Status)(m_Status | status);
}
void AppFrame::Application::RemoveStatus(Status status) {
	m_Status = (Status)(m_Status & ~status);
}
bool AppFrame::Application::IsStatus(Status status) {
	return m_Status & status;
}
AppFrame::Application::Status AppFrame::Application::GetStatus() {
	return m_Status;
}

AppFrame::Application::~Application() {}

/* these callbacks are used for module system. If happen some event/log then will be called these functions */
void AppFrame::Application::OnFatal		(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::fatal));
}
void AppFrame::Application::OnError		(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::error));
}
void AppFrame::Application::OnWarning	(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::warn));
}
void AppFrame::Application::OnInfo		(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::info));
}
void AppFrame::Application::OnTrace		(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::trace));
}
void AppFrame::Application::OnDebug		(const char * module, const char * file, unsigned int line, const char * msg) {
	EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::debug));
}