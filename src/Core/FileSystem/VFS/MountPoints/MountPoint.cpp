#include "MountPoint.h"
#include "Core/FileSystem/File.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <chrono>
#include <iostream>

AppFrame::MountPoint::MountPoint() {}

bool AppFrame::MountPoint::SetMountPoint(std::filesystem::path mountPoint) {
	m_MountPoint = mountPoint;

	m_watcherThread = std::thread(&MountPoint::StartWatcher, this);

	//std::async(std::launch::async, &MountPoint::StartWatcher, this);
	int a = 2;
	return true;
}
bool AppFrame::MountPoint::SetMountPriority(int priority) {
	m_Priority = priority;
	return true;
}

int AppFrame::MountPoint::Priority() {
	return m_Priority;
}

std::vector<std::filesystem::directory_entry> AppFrame::MountPoint::Directories(std::filesystem::path dir) {
	return std::vector<std::filesystem::directory_entry>();
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
std::shared_ptr<AppFrame::File> AppFrame::MountPoint::ReadFile(const std::filesystem::path & path) {
	return std::shared_ptr<AppFrame::File>();
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

AppFrame::MountPoint::~MountPoint() {
	m_watcherThread.join();
}

std::filesystem::path AppFrame::MountPoint::GetRealPath(std::filesystem::path file) {
	return std::filesystem::path(m_MountPoint / file);
}

void AppFrame::MountPoint::StartWatcher() {
	bool KeepWatching = true;
	std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(1000);
	while (KeepWatching) {
		std::this_thread::sleep_for(delay);

		auto it = m_FilesWatch.begin();
		while (it != m_FilesWatch.end()) {
			if (!std::filesystem::exists(it->first)) {
				//action(it->first, FileStatus::erased);
				it = m_FilesWatch.erase(it);
			} else {
				it++;
			}
		}

		// Check if a file was created or modified
		for (auto &file : std::filesystem::recursive_directory_iterator(m_MountPoint)) {
			auto current_file_last_write_time = std::filesystem::last_write_time(file);

			// File creation
			if (!Exist(file.path().string())) {
				m_FilesWatch[file.path().string()] = current_file_last_write_time;
				//action(file.path().string(), FileStatus::created);
			// File modification
			} else {
				if (m_FilesWatch[file.path().string()] != current_file_last_write_time) {
					m_FilesWatch[file.path().string()] = current_file_last_write_time;
					std::cout << "File modified: " << file.path().string() << std::endl;
					//action(file.path().string(), FileStatus::modified);
				}
			}
		}
	}
}

bool AppFrame::MountPoint::Exist(const std::string & key) {
	auto el = m_FilesWatch.find(key);
	return el != m_FilesWatch.end();
}
