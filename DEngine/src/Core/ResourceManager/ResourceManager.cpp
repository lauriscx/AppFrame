#include "ResourceManager.h"
#include <filesystem>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"

ResourceManager::ResourceManager() { }

template<typename T>
inline T * ResourceManager::GetResource(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle] == nullptr) {
		T* resource = new T();
		m_Resource[handle] = resource;
		//Load file
		if (!resource->load(path)) {
			return nullptr;
		}
		return resource;
	}

	return m_Resource[handle];
}

void ResourceManager::ReleaseResource(std::filesystem::path path) {
}

ResourceManager::~ResourceManager() { }