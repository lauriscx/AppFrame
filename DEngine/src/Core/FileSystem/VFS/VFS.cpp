#include "VFS.h"
#include "Core/FileSystem/VFS/VFS.h"

bool Engine::VFS::Mount(MountPoint* mount) {
	if (!MountExist(mount->GetPath())) {
		m_MountingPoints[mount->GetPath()] = mount;
		m_MountingPoints[mount->GetPath()]->OnMount();
		m_MountingPoints[mount->GetPath()]->SetMountPriority(m_MountingPoints.size());//For now priority will be by mounting priority.
		return true;
	}
	return false;
}

bool Engine::VFS::Unmount(const std::filesystem::path & _virtual) {
	if (MountExist(_virtual)) {
		m_MountingPoints[_virtual]->OnUnMount();
		m_MountingPoints.erase(_virtual);
		return true;
	}
	return false;
}

bool Engine::VFS::MountExist(const std::filesystem::path & _virtual) {
	auto moutingPoint = m_MountingPoints.find(_virtual);
	if (moutingPoint != m_MountingPoints.end()) {
		return true;
	}
	return false;
}

MountPoint * Engine::VFS::GetMount(std::filesystem::path mount) {
	auto moutingPoint = m_MountingPoints.find(mount);
	if (moutingPoint != m_MountingPoints.end()) {
		return moutingPoint->second;
	}
	return nullptr;
}

bool Engine::VFS::HasFile(const std::filesystem::path file) {
	for (auto mount : m_MountingPoints) {
		if (mount.second->HasFile(file)) {
			return true;
		}
	}
	return false;
}

bool Engine::VFS::HasDirectory(const std::filesystem::path directory) {
	for (auto mount : m_MountingPoints) {
		if (mount.second->HasDirectory(directory)) {
			return true;
		}
	}
	return false;
}

size_t Engine::VFS::FileSize(const std::filesystem::path file) {
	for (auto mount : m_MountingPoints) {
		int fileSize = mount.second->FileSize(file);
		if (fileSize != -1) {
			return fileSize;
		}
	}
	return -1;
}

bool Engine::VFS::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	for (auto mount : m_MountingPoints) {
		return mount.second->WriteFile(path, data, size);
	}
	return false;
}

char* Engine::VFS::ReadFile(const std::filesystem::path & path) {
	for (auto mount : m_MountingPoints) {
		return mount.second->ReadFile(path);
	}
	return nullptr;
}

bool Engine::VFS::CreateDirectory(const std::filesystem::path directory) {
	for (auto mount : m_MountingPoints) {
		return mount.second->CreateDirectory(directory);
	}
	return false;
}

bool Engine::VFS::CreateFile(const std::filesystem::path file, size_t size) {
	for (auto mount : m_MountingPoints) {
		return mount.second->CreateFile(file, size);
	}
	return false;
}

bool Engine::VFS::RemoveFile(const std::filesystem::path file) {
	for (auto mount : m_MountingPoints) {
		return mount.second->RemoveFile(file);
	}
	return false;
}

int Engine::VFS::RemoveDirectory(const std::filesystem::path directory) {
	for (auto mount : m_MountingPoints) {
		return mount.second->RemoveDirectory(directory);
	}
	return 0;
}
