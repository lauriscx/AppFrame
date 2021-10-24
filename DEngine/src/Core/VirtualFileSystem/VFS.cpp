#include "VFS.h"
#include "Core/FileSystem/FileSystem.h"

bool Engine::VFS::Mount(const std::filesystem::path & _virtual, const std::filesystem::path & physical) {
	if (strcmp(_virtual.string().c_str(), "") == 0 || strcmp(physical.string().c_str(), "") == 0 || MountExist(_virtual)) {
		return false;
	}
	m_MountPoints[_virtual] = physical;
	return true;
}

bool Engine::VFS::Unmount(const std::filesystem::path & _virtual) {
	if (strcmp(_virtual.string().c_str(), "") == 0 || !MountExist(_virtual)) {
		return false;
	}
	std::map<std::filesystem::path, std::filesystem::path>::iterator result = m_MountPoints.find(_virtual);
	m_MountPoints.erase(result);
	return true;
}

bool Engine::VFS::MountExist(const std::filesystem::path & _virtual) {
	return m_MountPoints.find(_virtual) != m_MountPoints.end();
}

bool Engine::VFS::GetPhysicPath(const std::filesystem::path & _virtual, std::filesystem::path * physic) {
	if (!MountExist(_virtual)) {
		return false;
	}
	*physic = m_MountPoints[_virtual];
	return true;
}

std::filesystem::path Engine::VFS::GetPath(const std::filesystem::path & _virtual) {
	/*
	 * Then path starts with / we want get path from virtual system.
	 * If path is without / we want physical path.
	 */
	if (_virtual.string()[0] != '/') {
		return _virtual;
	}
	std::filesystem::path PhysicalPath = m_MountPoints[FileSystem::get_root(_virtual)];
	PhysicalPath += FileSystem::strip_root(_virtual);

	return PhysicalPath;
}
