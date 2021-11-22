#include "RAMMountPoint.h"

RAMMountPoint::RAMMountPoint() {}

void RAMMountPoint::OnMount() {}
void RAMMountPoint::OnUnMount() {}

bool RAMMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool RAMMountPoint::HasFile(const std::filesystem::path file) {
	return false;
}
bool RAMMountPoint::HasDirectory(const std::filesystem::path directory) {
	return false;
}

size_t RAMMountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

bool RAMMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
char * RAMMountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool RAMMountPoint::CreateDirectory(const std::filesystem::path directory) {
	return false;
}
bool RAMMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool RAMMountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int RAMMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return 0;
}

RAMMountPoint::~RAMMountPoint() {}