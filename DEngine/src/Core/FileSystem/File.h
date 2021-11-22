#pragma once
#include <fstream>
#include <filesystem>

class File {
public:
	File();

	inline void SetData		(char* data						) { m_Data		= data; }
	inline void SetPath		(std::filesystem::path path		) { m_Path		= path; }
	inline void SetFolder	(std::filesystem::path folder	) { m_Folder	= folder; }
	inline void SetFile		(std::filesystem::path file		) { m_File		= file; }
	inline void SetExtension(const char* extension			) { m_Extension = extension; }

	~File();
private:
	char* m_Data;
	std::filesystem::path m_Path;
	std::filesystem::path m_Folder;
	std::filesystem::path m_File;
	std::string m_Extension;
};