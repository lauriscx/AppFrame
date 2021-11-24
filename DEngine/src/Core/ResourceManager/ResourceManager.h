#pragma once
#include "Resource.h"
#include <vector>
#include <FileSystem>
#include <map>

class ResourceManager {
public:
	ResourceManager();

	template <typename T>
	T* GetResource(std::filesystem::path path);
	void ReleaseResource(std::filesystem::path path);

	static ResourceManager* GetInstace() { static ResourceManager s_Instance; return &s_Instance; }

	virtual ~ResourceManager();

private:
	std::map<size_t, Resource*> m_Resource;

};


template<typename T>
T * ResourceManager::GetResource(std::filesystem::path path) {
	size_t handle = std::filesystem::hash_value(path);
	if (m_Resource[handle] == nullptr) {
		T* resource = new T();
		m_Resource[handle] = resource;
		//Load file
		if (!resource->Load(path)) {
			return nullptr;
		}
		return resource;
	}
	return (T*)m_Resource[handle];
}