#include "MountPoint.h""

MountPoint::MountPoint() {}

bool MountPoint::SetMountPoint(std::filesystem::path mountPoint) {
	m_MountPoint = mountPoint;
	return false;
}

bool MountPoint::SetMountPriority(int priority) {
	return false;
}

void MountPoint::OnMount() { }

void MountPoint::OnUnMount() { }

bool MountPoint::HasFile(const std::filesystem::path file) {
	return false;
}

bool MountPoint::HasDirectory(const std::filesystem::path file) {
	return false;
}

size_t MountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

std::filesystem::path MountPoint::GetPath() {
	return m_MountPoint;
}

int MountPoint::Priority() {
	return m_Priority;
}

bool MountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}

char* MountPoint::ReadFile(const std::filesystem::path & path, size_t size) {
	return false;
}

bool MountPoint::CreateDirectory(const std::filesystem::path file) {
	return false;
}

bool MountPoint::CreateFile(const std::filesystem::path file) {
	return false;
}

bool MountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}

int MountPoint::RemoveDirectory(const std::filesystem::path directory)
{
	return false;
}

MountPoint::~MountPoint() { }