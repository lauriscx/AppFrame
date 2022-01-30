#include "Core/FileSystem/VFS/MountPoints/RAMMountPoint.h"
#include "Core/FileSystem/File.h"

AppFrame::RAMMountPoint::RAMMountPoint() {}

void AppFrame::RAMMountPoint::OnMount() {}
void AppFrame::RAMMountPoint::OnUnMount() {}

bool AppFrame::RAMMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool AppFrame::RAMMountPoint::HasFile(const std::filesystem::path file) {
	return false;
}
bool AppFrame::RAMMountPoint::HasDirectory(const std::filesystem::path directory) {
	return false;
}

size_t AppFrame::RAMMountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

bool AppFrame::RAMMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
bool AppFrame::RAMMountPoint::WriteFile(File * file) {
	return WriteFile(file->GetPath(), file->GetData(), file->GetSize());
}
AppFrame::File* AppFrame::RAMMountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool AppFrame::RAMMountPoint::CreateDirectory(const std::filesystem::path directory) {
	return false;
}
bool AppFrame::RAMMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool AppFrame::RAMMountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int AppFrame::RAMMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return 0;
}

AppFrame::RAMMountPoint::~RAMMountPoint() {}