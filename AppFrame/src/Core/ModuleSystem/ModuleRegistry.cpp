#include "ModuleRegistry.h"

Engine::ModuleRegistry::ModuleRegistry() { }

void Engine::ModuleRegistry::OnEarlyUpdate(float deltaTime) {
	for (auto module : m_EarlyUpdate) {
		module.second->OnEarlyUpdate(deltaTime);
	}
}
void Engine::ModuleRegistry::OnMiddleUpdate(float deltaTime) {
	for (auto module : m_MiddleUpdate) {
		module.second->OnUpdate(deltaTime);
	}
}
void Engine::ModuleRegistry::OnLateUpdate(float deltaTime) {
	for (auto module : m_LateUpdate) {
		module.second->OnLateUpdate(deltaTime);
	}
}

void Engine::ModuleRegistry::SetOnFatal(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnFatal = func;
}
void Engine::ModuleRegistry::SetOnError(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnError = func;
}
void Engine::ModuleRegistry::SetOnWarning(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnWarning = func;
}
void Engine::ModuleRegistry::SetOnInfo(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnInfo = func;
}
void Engine::ModuleRegistry::SetOnTrace(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnTrace = func;
}
void Engine::ModuleRegistry::SetOnDebug(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnDebug = func;
}

Engine::ModuleRegistry::~ModuleRegistry() { }

void Engine::ModuleRegistry::SetUpModule(Module * module) {
	module->Fatal	= OnFatal;
	module->Error	= OnError;
	module->Warning = OnWarning;
	module->Info	= OnInfo;
	module->Trace	= OnTrace;
	module->Debug	= OnDebug;
}