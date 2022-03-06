#pragma once
#include "Core/Core.h"
#include "Resource.h"

namespace AppFrame {
	class ResourceManager {
	private:
		ResourceManager() {}
	public:

		template <typename T>
		const T &GetResource(std::filesystem::path path);

		template <typename T>
		const T* LookResource(std::filesystem::path path);

		const bool IsAvailable(std::filesystem::path path);

		void CleanUnusedResource();

		inline std::map<uint32_t, Resource*>& GetResources() { return m_Resource; }

		void ReleaseResources();

		static ResourceManager* GetInstance() { static ResourceManager s_Instance; return &s_Instance; }

		virtual ~ResourceManager();

	private:
		std::map<uint32_t, Resource*> m_Resource;
	};

	template<typename T>
	const T &ResourceManager::GetResource(std::filesystem::path path) {
		uint32_t handle = std::filesystem::hash_value(path);;

		if (m_Resource.find(handle) == m_Resource.end()) {//Create if not exist and then load.
			m_Resource[handle] = new T(path);
			static_cast<T*>(m_Resource[handle])->Load(path);
		}

		return *static_cast<T*>(m_Resource[handle]);
	}

	template<typename T>
	const T * ResourceManager::LookResource(std::filesystem::path path) {
		uint32_t handle = std::filesystem::hash_value(path);;
		return static_cast<T*>(&m_Resource[handle]);
	}
}