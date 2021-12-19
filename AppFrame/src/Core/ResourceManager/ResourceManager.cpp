#include "ResourceManager.h"
#include <filesystem>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"
#include <iostream>

ResourceManager::ResourceManager() { }

void ResourceManager::ReleaseResource(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle].second != nullptr) {
		m_Resource[handle].first--;
		if (m_Resource[handle].first == 0) {
			m_Resource[handle].second->OnRelease();
			delete m_Resource[handle].second;//Deleting created resource
			m_Resource.erase(handle);//Removed from resource manager
			std::cout << "Releasing " << path << " handle " << handle << std::endl;
		}
	}
}

const bool ResourceManager::IsAvailable(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle].second == nullptr) {
		return false;
	}
	return true;
}

ResourceManager::~ResourceManager() { 
	for (auto resource : m_Resource) {
		resource.second.first = 0;
		if (resource.second.second != nullptr) {
			resource.second.second->OnRelease();
			delete resource.second.second;
		}
	}

}