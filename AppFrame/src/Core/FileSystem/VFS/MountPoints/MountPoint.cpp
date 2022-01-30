#include "MountPoint.h"
#include "Core/FileSystem/File.h"

AppFrame::MountPoint::MountPoint() {}

bool AppFrame::MountPoint::SetMountPoint(std::filesystem::path mountPoint) {
	m_MountPoint = mountPoint;
	return true;
}
bool AppFrame::MountPoint::SetMountPriority(int priority) {
	m_Priority = priority;
	return true;
}

int AppFrame::MountPoint::Priority() {
	return m_Priority;
}

std::filesystem::path AppFrame::MountPoint::GetPath() {
	return m_MountPoint;
}

bool AppFrame::MountPoint::CreateMount(const std::filesystem::path file){
	return false;
}

void AppFrame::MountPoint::OnMount() { }
void AppFrame::MountPoint::OnUnMount() { }

bool AppFrame::MountPoint::HasFile(const std::filesystem::path file) {
	return false;
}
bool AppFrame::MountPoint::HasDirectory(const std::filesystem::path file) {
	return false;
}

size_t AppFrame::MountPoint::FileSize(const std::filesystem::path file) {
	return size_t();
}

bool AppFrame::MountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
bool AppFrame::MountPoint::WriteFile(File * file) {
	return WriteFile(file->GetPath(), file->GetData(), file->GetSize());
}
AppFrame::File* AppFrame::MountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool AppFrame::MountPoint::CreateDirectory(const std::filesystem::path file) {
	return false;
}
bool AppFrame::MountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool AppFrame::MountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int AppFrame::MountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return false;
}

AppFrame::MountPoint::~MountPoint() { }

std::filesystem::path AppFrame::MountPoint::GetRealPath(std::filesystem::path file) {
	return std::filesystem::path(m_MountPoint.u32string() + file.u32string());
}