#pragma once
#include "Core/Core.h"
#include <filesystem>
#include <map>
#include "MountPoints/MountPoint.h"

class File;
namespace AppFrame {
	class VFS {
	public:
		bool Mount(MountPoint* mount);
		bool Unmount(const std::filesystem::path& _virtual);
		bool MountExist(const std::filesystem::path& _virtual);

		MountPoint* GetMount(std::filesystem::path mount);

		bool HasFile(const std::filesystem::path file);
		bool HasDirectory(const std::filesystem::path directory);
		size_t FileSize(const std::filesystem::path file);

		bool WriteFile(const std::filesystem::path& path, char* data, size_t size);
		bool WriteFile(File* file);
		std::shared_ptr<File> ReadFile(const std::filesystem::path& path);

		bool CreateDirectory(const std::filesystem::path directory);
		bool CreateFile(const std::filesystem::path file, size_t size);
		bool RemoveFile(const std::filesystem::path file);
		int RemoveDirectory(const std::filesystem::path directory);


		static VFS* GetInstance() { static VFS s_Instance; return &s_Instance; }
	private:
		std::map<std::filesystem::path, MountPoint*> m_MountingPoints;
	};
}