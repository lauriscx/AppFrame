#include "Core/ResourceManager/ResourceManager.h"

const bool AppFrame::ResourceManager::IsAvailable(std::filesystem::path path) {
	auto hand = std::filesystem::hash_value(path);
	return m_Resource[hand]->IsAvailable();
}

void AppFrame::ResourceManager::CleanUnusedResource() {
	for (auto it = m_Resource.cbegin(); it != m_Resource.cend(); ) {
		if (it->second->getRefCount() <= 1) {
			it->second->OnRelease();
			delete it->second;
			m_Resource.erase(it++);
		} else {
			++it;
		}
	}
}

void AppFrame::ResourceManager::ReleaseResources() {
	for (auto resource : m_Resource) {
		resource.second->OnRelease();
		delete resource.second;
	}
	m_Resource.clear();
}

AppFrame::ResourceManager::~ResourceManager() {
	for (auto resource : m_Resource) {
		resource.second->OnRelease();
		delete resource.second;
	}
	m_Resource.clear();
}