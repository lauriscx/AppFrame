#include "CloudMountPoint.h"

CloudMountPoint::CloudMountPoint() {}

void CloudMountPoint::OnMount() {}
void CloudMountPoint::OnUnMount() {}

bool CloudMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool CloudMountPoint::HasFile(const std::filesystem::path file) {
	return false;
}
bool CloudMountPoint::HasDirectory(const std::filesystem::path directory) {
	return false;
}

size_t CloudMountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

bool CloudMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
char * CloudMountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool CloudMountPoint::CreateDirectory(const std::filesystem::path directory) {
	return false;
}
bool CloudMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool CloudMountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int CloudMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return 0;
}

CloudMountPoint::~CloudMountPoint() {}