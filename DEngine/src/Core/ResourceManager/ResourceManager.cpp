#include "ResourceManager.h"
#include <filesystem>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"

ResourceManager::ResourceManager() { }

void ResourceManager::ReleaseResource(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle] != nullptr) {
		m_Resource[handle]->OnRelease();
	}
}

const bool ResourceManager::IsAvailable(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle] == nullptr) {
		return false;
	}
	return true;
}

ResourceManager::~ResourceManager() { }