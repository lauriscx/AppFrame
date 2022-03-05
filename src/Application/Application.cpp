#include "Application.h"
#include "Application/Events/AppEvents.h"
#include <functional>
#include "Core/EventSystem/EventManager.h"
#include "optick.h"

AppFrame::Application* AppFrame::Application::s_Instance = nullptr;

AppFrame::Application::Application(AppFrame::AppConfig* config) : EventHandler("Application"), AppContext(config) {
	OPTICK_APP(config->GetApplicationName().c_str());
	OPTICK_SET_MEMORY_ALLOCATOR(
		[](size_t size) -> void* { return operator new(size); },
		[](void* p) { operator delete(p); },
		[]() { /* Do some TLS initialization here if needed */ }
	);
	OPTICK_FRAME("MainThread");
	/* Important init data only in run function */
}

void AppFrame::Application::Run() {
	//AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceMesh>("");
	OPTICK_EVENT();
	m_Device = new Device();

	for (auto module : m_Modules) {
		module.second->OnInit(this);
	}
	for (auto module : m_Modules) {
		module.second->OnStart();
	}
}

void AppFrame::Application::OnEarlyUpdate() {
	OPTICK_EVENT();
	m_Timer.Start();
	ModuleRegistry::OnEarlyUpdate(m_Timer.Elapsed());
}
void AppFrame::Application::OnUpdate	() {
	OPTICK_EVENT();
	ModuleRegistry::OnMiddleUpdate(m_Timer.Elapsed());
}
void AppFrame::Application::OnLateUpdate() {
	OPTICK_EVENT();
	ModuleRegistry::OnLateUpdate(m_Timer.Elapsed());
	m_Timer.Stop();
}

bool AppFrame::Application::OnEvent	(BasicEvent & event) {
	OPTICK_EVENT();
	for (auto module : m_Modules) {
		module.second->OnAppEvent(&event);
	}
	return false;
}
bool AppFrame::Application::OnInput(const InputData& input) {
	OPTICK_EVENT();
	OPTICK_CATEGORY("UpdateInput", Optick::Category::Input);
	return false;
}

AppFrame::AppConfig		* AppFrame::Application::GetConfig	() {
	OPTICK_EVENT();
	return m_Config;
}

AppFrame::Device	* AppFrame::Application::GetDevice	() {
	OPTICK_EVENT();
	return m_Device;
}

void AppFrame::Application::Stop	() {
	OPTICK_EVENT();
	for (auto module : m_Modules) {
		module.second->OnStop();
	}
}

AppFrame::Application::~Application() {
	OPTICK_SHUTDOWN();
}