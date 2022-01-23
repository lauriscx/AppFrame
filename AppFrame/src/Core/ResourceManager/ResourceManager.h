#pragma once
#include "Core/Core.h"
#include "Resource.h"
#include <vector>
#include <FileSystem>
#include <map>
#include <tuple>
#include <iostream>

namespace AppFrame {
	class ENGINE_API ResourceManager {
	public:
		ResourceManager();

		template <typename T>
		T* GetResource(std::filesystem::path path);
		void ReleaseResource(std::filesystem::path path);
		const bool IsAvailable(std::filesystem::path path);

		static ResourceManager* GetInstance() { static ResourceManager s_Instance; return &s_Instance; }

		virtual ~ResourceManager();

	private:
		std::map<rsize_t, std::pair<size_t, Resource*>> m_Resource;
	};

	template<typename T>
	T * ResourceManager::GetResource(std::filesystem::path path) {
		size_t handle = std::filesystem::hash_value(path);
		if (m_Resource[handle].second == nullptr) {
			T* resource = new T();
			//Load file
			if (!resource->Load(path)) {
				std::cout << "Failed to load resource " << path << " handle " << handle << std::endl;
				delete resource;//release memory
				return nullptr;
			}
			std::cout << "Succesfully loaded resource " << path << " handle " << handle << std::endl;
			m_Resource[handle] = std::make_pair(1, resource);
			return resource;
		}
		m_Resource[handle].first++;
		return static_cast<T*>(m_Resource[handle].second);
	}
}