#pragma once
#include "Core/Core.h"
#include <vector>
#include <unordered_map>
#include <map>

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>
#include <thread>

namespace AppFrame {
	class File;

	class MountPoint {
	public:
		MountPoint();

		virtual bool SetMountPoint(std::filesystem::path mountPoint);
		virtual bool SetMountPriority(int priority);

		virtual bool CreateMount(const std::filesystem::path file);

		virtual void OnMount();
		virtual void OnUnMount();

		virtual bool HasFile(const std::filesystem::path file);
		virtual bool HasDirectory(const std::filesystem::path directory);

		virtual size_t FileSize(const std::filesystem::path file);

		virtual bool WriteFile(const std::filesystem::path& path, char* data, size_t size);
		virtual bool WriteFile(File* file);
		virtual std::shared_ptr<AppFrame::File> ReadFile(const std::filesystem::path& path);

		virtual bool CreateDirectory(const std::filesystem::path directory);
		virtual bool CreateFile(const std::filesystem::path file, size_t size);

		virtual bool RemoveFile(const std::filesystem::path file);
		virtual int RemoveDirectory(const std::filesystem::path directory);

		virtual std::filesystem::path GetPath();
		virtual int Priority();

		virtual std::vector<std::filesystem::directory_entry> Directories(std::filesystem::path dir = "");


		virtual ~MountPoint();

	protected:
		std::filesystem::path GetRealPath(std::filesystem::path file);

		std::filesystem::path m_MountPoint;
		std::vector<std::filesystem::path> m_Files;

		//Map off functions/callbacks of releated file and action. Created, modyfied, deleted, renamed.
		std::map<std::filesystem::path, std::filesystem::file_time_type> m_FilesWatch;

		std::thread m_watcherThread;

		void StartWatcher();
		bool Exist(const std::string &key);

		int m_Priority;

	};
}