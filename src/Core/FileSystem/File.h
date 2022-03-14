#pragma once
#include "Core/Core.h"
#include <fstream>
#include <filesystem>

namespace AppFrame {
	class File {
	public:
		File();

		void SetData(char* data);
		void SetSize(const uint32_t size);
		void SetFullPath(const std::filesystem::path path);
		void SetPath(const std::filesystem::path path);
		void SetFolder(const std::filesystem::path folder);
		void SetFile(const std::filesystem::path file);
		void SetExtension(const std::filesystem::path extension);

		bool IsDataAvailable();

		std::filesystem::path	GetFullPath();
		std::filesystem::path	GetPath();
		char*					GetData();
		uint32_t				GetSize();

		~File();
	private:
		char* m_Data;
		std::filesystem::path m_FullPath;
		std::filesystem::path m_Path;
		std::filesystem::path m_Folder;
		std::filesystem::path m_File;
		std::filesystem::path m_Extension;
		uint32_t m_FileSize;
	};
}