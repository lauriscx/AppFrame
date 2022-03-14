#pragma once
#include "Core/Core.h"
#include <filesystem>

#include "Core/FileSystem/File.h"
#include "Core/FileSystem/VFS/VFS.h"

#include <mutex>

//#define DEBUG_RES

#ifdef DEBUG_RES
	#include <iostream>
#endif

namespace AppFrame {
	class Resource {
	public:
		Resource() {
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_RefCount = new uint32_t(0);
			if (m_RefCount) {
				(*m_RefCount)++;
			}

			#ifdef DEBUG_RES
				std::cout << "Resource() " << *m_RefCount << std::endl;
			#endif
		}

		Resource(std::filesystem::path file) : m_File(file) {
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_RefCount = new uint32_t(0);
			if (m_RefCount) {
				(*m_RefCount)++;
			}

			#ifdef DEBUG_RES
				std::cout << "Resource(std::filesystem::path file) " << *m_RefCount << std::endl;
			#endif
		}

		Resource(Resource& sp) {
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_RefCount = sp.m_RefCount;
			m_File = sp.m_File;
			(*m_RefCount)++;

			#ifdef DEBUG_RES
				std::cout << "Resource(Resource& sp) " << *m_RefCount << std::endl;
			#endif
		}

		Resource(const Resource& sp) {
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_RefCount = sp.m_RefCount;
			m_File = sp.m_File;
			(*m_RefCount)++;

			#ifdef DEBUG_RES
				std::cout << "Resource(const Resource& sp) " << *m_RefCount << std::endl;
			#endif
		}

		Resource& operator=(const Resource& other) {
			std::lock_guard<std::mutex> lock(m_Mutex);
			(*this->m_RefCount)--;
			(*other.m_RefCount)++;

			this->m_RefCount = other.m_RefCount;
			this->m_File = other.m_File;
			
			#ifdef DEBUG_RES
				std::cout << "Resource& operator=(const Resource& other) " << *m_RefCount << std::endl;
			#endif

			return *this;
		}

		bool isValid() { std::lock_guard<std::mutex> lock(m_Mutex); return m_RefCount != nullptr && (*m_RefCount) > 0; }

		virtual bool IsAvailable() = 0;
		virtual bool Load(std::filesystem::path file) = 0;

		virtual void OnLoad() = 0;
		virtual void OnRelease() = 0;

		virtual size_t GetMemoryUsage() = 0;

		std::filesystem::path GetPath() { std::lock_guard<std::mutex> lock(m_Mutex); return m_File; }
		uint32_t getRefCount() { std::lock_guard<std::mutex> lock(m_Mutex); return *m_RefCount; }

		virtual ~Resource() {
			std::lock_guard<std::mutex> lock(m_Mutex);
			if (m_RefCount) {
				(*m_RefCount)--;
			}

			#ifdef DEBUG_RES
				std::cout << "~Resource() " << *m_RefCount << std::endl;
			#endif

			if (*m_RefCount == 0) {
				delete m_RefCount;
			}
		}

	protected:
		std::filesystem::path m_File;
		uint32_t* m_RefCount;
		std::mutex m_Mutex;
	};
}