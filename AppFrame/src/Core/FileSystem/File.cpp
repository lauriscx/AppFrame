#include "File.h"

File::File() {}

void File::SetData		(char * data							) {
	m_Data = data;
}
void File::SetSize		(const uint32_t size					) {
	m_FileSize = size;
}
void File::SetPath		(const std::filesystem::path path		) {
	m_Path		= path;
	m_Folder	= path.parent_path();
	m_File		= path.filename();
	m_Extension = path.extension();
}
void File::SetFolder	(const std::filesystem::path folder		) {
	m_Folder = folder;
}
void File::SetFile		(const std::filesystem::path file		) {
	m_File = file;
}
void File::SetExtension	(const std::filesystem::path extension	) {
	m_Extension = extension;
}

bool File::IsDataAvailable() {
	return m_Data != nullptr;
}

std::filesystem::path	File::GetPath() {
	return m_Folder / m_File;
}
char *					File::GetData() {
	return m_Data;
}
uint32_t				File::GetSize() {
	return m_FileSize;
}

File::~File() {
	delete[] m_Data;
}