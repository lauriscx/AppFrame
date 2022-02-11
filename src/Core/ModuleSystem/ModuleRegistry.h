#pragma once
#include "Core/Core.h"
#include "Module.h"
#include <unordered_map>
#include <map>
#include <vector>

namespace AppFrame {
	class ModuleRegistry {
	public:
		ModuleRegistry();

		template<typename T>
		void AddModule(T* module, unsigned int Early, unsigned int middle, unsigned int late);//change to use memory ref.
		template<typename T>
		void AddModule(T* module, unsigned int index);//change to use memory ref.
		template<typename T>
		void AddModule(T* module);//change to use memory ref.

		virtual void OnEarlyUpdate(float deltaTime);
		virtual void OnMiddleUpdate(float deltaTime);
		virtual void OnLateUpdate(float deltaTime);
		
		template <typename T>
		T* GetModule();
		
		~ModuleRegistry();

	protected:
		std::unordered_map<std::string, Module*> m_Modules;
		std::map<unsigned int, Module*> m_EarlyUpdate;
		std::map<unsigned int, Module*> m_MiddleUpdate;
		std::map<unsigned int, Module*> m_LateUpdate;
	};

	template<typename T>
	inline void ModuleRegistry::AddModule(T * module, unsigned int Early, unsigned int middle, unsigned int late) {
		m_Modules[typeid(T).name()] = module;
		m_EarlyUpdate[Early] = module;
		m_MiddleUpdate[middle] = module;
		m_LateUpdate[late] = module;
	}
	template<typename T>
	inline void ModuleRegistry::AddModule(T * module, unsigned int index) {
		m_Modules[typeid(T).name()] = module;
		m_EarlyUpdate[index] = module;
		m_MiddleUpdate[index] = module;
		m_LateUpdate[index] = module;
	}
	template<typename T>
	inline void ModuleRegistry::AddModule(T * module) {
		m_Modules[typeid(T).name()] = module;
		m_EarlyUpdate[m_EarlyUpdate.size() - 1] = module;
		m_MiddleUpdate[m_MiddleUpdate.size() - 1] = module;
		m_LateUpdate[m_LateUpdate.size() - 1] = module;
	}

	template<typename T>
	inline T* ModuleRegistry::GetModule() {
		return  static_cast<T*>(m_Modules[typeid(T).name()]);
	}
}