#pragma once
#include "Core/Core.h"
#include "Core/DataTypes.h"
#include <filesystem>

namespace Engine {
	class ENGINE_API FileSystem {
	public:
		static bool IsFileExists		(const std::filesystem::path& path);
		static bool IsDirectoryExist	(const std::filesystem::path& path);
		static bool FileSize			(const std::filesystem::path& path, int64* size);
			 
		static bool CreateDirectory		(const std::filesystem::path& path);
		static bool CreateFile			(const std::filesystem::path& path);
			 
		static bool WriteTextFile		(const std::filesystem::path& path, const char* data);
		static bool ReadTextFile		(const std::filesystem::path& path, const char* data);
			 
		static bool WriteBinaryFile		(const std::filesystem::path& path, byte* data, size_t size);
		static bool ReadBinaryFile		(const std::filesystem::path& path, byte* data, size_t size);
			 
		static bool RemoveFile			(const std::filesystem::path& path);

		static std::filesystem::path strip_root	(const std::filesystem::path& path);
		static std::filesystem::path get_root	(const std::filesystem::path& path);

	private:
		FileSystem	() {}
		FileSystem	(const FileSystem& fileSystem) {}
		FileSystem	(const FileSystem&& fileSystem) {}
		~FileSystem	() {}
	};
}