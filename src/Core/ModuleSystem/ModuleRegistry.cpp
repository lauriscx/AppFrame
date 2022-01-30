#include "ModuleRegistry.h"

AppFrame::ModuleRegistry::ModuleRegistry() { }

void AppFrame::ModuleRegistry::OnEarlyUpdate(float deltaTime) {
	for (auto module : m_EarlyUpdate) {
		module.second->OnEarlyUpdate(deltaTime);
	}
}
void AppFrame::ModuleRegistry::OnMiddleUpdate(float deltaTime) {
	for (auto module : m_MiddleUpdate) {
		module.second->OnUpdate(deltaTime);
	}
}
void AppFrame::ModuleRegistry::OnLateUpdate(float deltaTime) {
	for (auto module : m_LateUpdate) {
		module.second->OnLateUpdate(deltaTime);
	}
}

void AppFrame::ModuleRegistry::SetOnFatal(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnFatal = func;
}
void AppFrame::ModuleRegistry::SetOnError(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnError = func;
}
void AppFrame::ModuleRegistry::SetOnWarning(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnWarning = func;
}
void AppFrame::ModuleRegistry::SetOnInfo(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnInfo = func;
}
void AppFrame::ModuleRegistry::SetOnTrace(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnTrace = func;
}
void AppFrame::ModuleRegistry::SetOnDebug(std::function<void(const char*, const char*, unsigned int, const char*)> func) {
	OnDebug = func;
}

AppFrame::ModuleRegistry::~ModuleRegistry() { }

void AppFrame::ModuleRegistry::SetUpModule(Module * module) {
	module->Fatal	= OnFatal;
	module->Error	= OnError;
	module->Warning = OnWarning;
	module->Info	= OnInfo;
	module->Trace	= OnTrace;
	module->Debug	= OnDebug;
}