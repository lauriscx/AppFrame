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

AppFrame::ModuleRegistry::~ModuleRegistry() { }