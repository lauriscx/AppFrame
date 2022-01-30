#include "CloudMountPoint.h"
#include "FileSystem/File.h"

AppFrame::CloudMountPoint::CloudMountPoint() {}

void AppFrame::CloudMountPoint::OnMount() {}
void AppFrame::CloudMountPoint::OnUnMount() {}

bool AppFrame::CloudMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool AppFrame::CloudMountPoint::HasFile(const std::filesystem::path file) {
	return false;
}
bool AppFrame::CloudMountPoint::HasDirectory(const std::filesystem::path directory) {
	return false;
}

size_t AppFrame::CloudMountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

bool AppFrame::CloudMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
bool AppFrame::CloudMountPoint::WriteFile(File * file) {
	return WriteFile(file->GetPath(), file->GetData(), file->GetSize());
}
AppFrame::File* AppFrame::CloudMountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool AppFrame::CloudMountPoint::CreateDirectory(const std::filesystem::path directory) {
	return false;
}
bool AppFrame::CloudMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool AppFrame::CloudMountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int AppFrame::CloudMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return 0;
}

AppFrame::CloudMountPoint::~CloudMountPoint() {}