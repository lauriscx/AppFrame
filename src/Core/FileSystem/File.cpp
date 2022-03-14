#include "File.h"

AppFrame::File::File() {}

void AppFrame::File::SetData		(char * data							) {
	m_Data = data;
}
void AppFrame::File::SetSize		(const uint32_t size					) {
	m_FileSize = size;
}
void AppFrame::File::SetFullPath(const std::filesystem::path path			) {
	m_FullPath = path;
}
void AppFrame::File::SetPath		(const std::filesystem::path path		) {
	m_Path		= path;
	m_Folder	= path.parent_path();
	m_File		= path.filename();
	m_Extension = path.extension();
}
void AppFrame::File::SetFolder	(const std::filesystem::path folder			) {
	m_Folder = folder;
}
void AppFrame::File::SetFile		(const std::filesystem::path file		) {
	m_File = file;
}
void AppFrame::File::SetExtension	(const std::filesystem::path extension	) {
	m_Extension = extension;
}

bool AppFrame::File::IsDataAvailable() {
	return m_Data != nullptr;
}

std::filesystem::path AppFrame::File::GetFullPath() {
	return m_FullPath;
}
std::filesystem::path	AppFrame::File::GetPath() {
	return m_Folder / m_File;
}
char *					AppFrame::File::GetData() {
	return m_Data;
}
uint32_t				AppFrame::File::GetSize() {
	return m_FileSize;
}

AppFrame::File::~File() {
	delete[] m_Data;
}