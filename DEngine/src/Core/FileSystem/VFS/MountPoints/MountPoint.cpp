#include "MountPoint.h"
#include "FileSystem/File.h"

MountPoint::MountPoint() {}

bool MountPoint::SetMountPoint(std::filesystem::path mountPoint, std::filesystem::path folder) {
	m_MountPoint = mountPoint;
	m_Folder = folder;
	return true;
}
bool MountPoint::SetMountPriority(int priority) {
	m_Priority = priority;
	return true;
}

int MountPoint::Priority() {
	return m_Priority;
}

std::filesystem::path MountPoint::GetPath() {
	return m_MountPoint;
}

bool MountPoint::CreateMount(const std::filesystem::path file){
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

bool MountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	return false;
}
bool MountPoint::WriteFile(File * file) {
	return WriteFile(file->GetPath(), file->GetData(), file->GetSize());
}
File* MountPoint::ReadFile(const std::filesystem::path & path) {
	return nullptr;
}

bool MountPoint::CreateDirectory(const std::filesystem::path file) {
	return false;
}
bool MountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	return false;
}

bool MountPoint::RemoveFile(const std::filesystem::path file) {
	return false;
}
int MountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return false;
}

MountPoint::~MountPoint() { }

std::filesystem::path MountPoint::GetRealPath(std::filesystem::path file) {
	std::filesystem::path test = m_MountPoint / strip_root(file);
	return test;
}

std::filesystem::path MountPoint::strip_root(const std::filesystem::path & path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/") {
		return std::filesystem::path();
	} else {
		return strip_root(parent_path) += "/" + path.filename().string();
	}
}

std::filesystem::path MountPoint::get_root(const std::filesystem::path & path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/") {
		return path;
	} else {
		return get_root(parent_path);
	}
}
