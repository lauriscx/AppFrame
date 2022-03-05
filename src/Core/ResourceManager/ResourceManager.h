#pragma once
#include "Core/Core.h"
#include "Resource.h"
#include <vector>
#include <FileSystem>
#include <map>
#include <tuple>
#include <iostream>



#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Core/ResourceManager/ResourceManager.h"
#include "Application/Resources/ResourceMesh.h"
#include "Core/ResourceManager/Resource.h"

#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include "Core/ResourceManager/ResourceManager.h"

#include <filesystem>
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"

namespace AppFrame {
	class ResourceManager {
	public:
		ResourceManager();

		template <typename T>
		T GetResource(std::filesystem::path path);
		template <typename T>
		T* LookResource(std::filesystem::path path);
		void ReleaseResource(std::filesystem::path path);

		template <typename T>
		void ReleaseResource(T* resource);

		const bool IsAvailable(std::filesystem::path path);

		static ResourceManager* GetInstance() { static ResourceManager s_Instance; return &s_Instance; }

		virtual ~ResourceManager();

	private:
		std::map<rsize_t, std::pair<size_t, Resource>> m_Resource;
	};

	template<typename T>
	T ResourceManager::GetResource(std::filesystem::path path) {
		size_t handle = std::filesystem::hash_value(path);
		if (!m_Resource[handle].second.IsAvailable()) {
			T resource;
			//Load file
			if (!resource.Load(path)) {
				std::cout << "Failed to load resource " << path << " handle " << handle << std::endl;
				return {};
			}
			std::cout << "Succesfully loaded resource " << path << " handle " << handle << std::endl;
			m_Resource[handle] = std::make_pair(1, resource);
			return resource;
		}
		m_Resource[handle].first++;
		T res = *(dynamic_cast<T*>(&m_Resource[handle].second));
		return res;
	}

	template<typename T>
	T * ResourceManager::LookResource(std::filesystem::path path) {
		size_t handle = std::filesystem::hash_value(path);
		return static_cast<T*>(&m_Resource[handle].second);
	}

	template<typename T>
	inline void ResourceManager::ReleaseResource(T * resource) {
		size_t handle = std::filesystem::hash_value(resource->GetPath());
		if (resource->IsAvailable()) {
			m_Resource[handle].first--;
			if (m_Resource[handle].first <= 1) {
				resource->OnRelease();
				m_Resource.erase(handle);//Removed from resource manager
				std::cout << "Releasing " << resource->GetPath() << " handle " << handle << std::endl;
			}
		}
	}
}