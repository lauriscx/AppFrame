#pragma once
#include "Core/Core.h"
#include "Core/DataTypes.h"
#include <filesystem>

namespace Engine {
	class ENGINE_API FileSystem {
	public:
		static bool IsFileExists		(std::filesystem::path path);
		static bool IsDirectoryExist	(std::filesystem::path path);
		static bool FileSize			(std::filesystem::path path, int64* size);
			 
		static bool CreateDirectory		(std::filesystem::path path);
		static bool CreateFile			(std::filesystem::path path);
			 
		static bool WriteTextFile		(std::filesystem::path path, const char* data);
		static bool ReadTextFile		(std::filesystem::path path, const char* data);
			 
		static bool WriteBinaryFile		(std::filesystem::path path, byte* data, size_t size);
		static bool ReadBinaryFile		(std::filesystem::path path, byte* data, size_t size);
			 
		static bool RemoveFile			(std::filesystem::path path);

	private:
		FileSystem	() {}
		FileSystem	(const FileSystem& fileSystem) {}
		FileSystem	(const FileSystem&& fileSystem) {}
		~FileSystem	() {}
	};
}