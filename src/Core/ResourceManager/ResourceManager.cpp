#include "ResourceManager.h"
#include <filesystem>
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"

AppFrame::ResourceManager::ResourceManager() { }

void AppFrame::ResourceManager::ReleaseResource(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle].second.IsAvailable()) {
		m_Resource[handle].first--;
		if (m_Resource[handle].first <= 1) {
			m_Resource[handle].second.OnRelease();
			m_Resource.erase(handle);//Removed from resource manager
			std::cout << "Releasing " << path << " handle " << handle << std::endl;
		}
	}
}

const bool AppFrame::ResourceManager::IsAvailable(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle].second.IsAvailable()) {
		return false;
	}
	return true;
}

AppFrame::ResourceManager::~ResourceManager() {
	for (auto resource : m_Resource) {
		resource.second.first = 0;
		//if (resource.second.second.IsAvailable()) {
			resource.second.second.OnRelease();
		//}
	}
	//m_Resource.clear();
}