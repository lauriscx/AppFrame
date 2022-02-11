#include "Application.h"
#include "Application/Events/AppEvents.h"
#include <functional>
#include "Core/EventSystem/EventManager.h"

AppFrame::Application* AppFrame::Application::s_Instance = nullptr;

AppFrame::Application::Application(AppFrame::AppConfig* config) : EventHandler("Application"), AppContext(config) {
	/* Important init data only in run function */
}

void AppFrame::Application::Run() {
	m_Device = new Device();

	for (auto module : m_Modules) {
		module.second->OnInit(this);
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
bool AppFrame::Application::OnInput(const InputData& input) {
	return false;
}

AppFrame::AppConfig		* AppFrame::Application::GetConfig	() {
	return m_Config;
}

AppFrame::Device	* AppFrame::Application::GetDevice	() {
	return m_Device;
}

void AppFrame::Application::Stop	() {
	for (auto module : m_Modules) {
		module.second->OnStop();
	}
}

AppFrame::Application::~Application() {}