#include "PhysicalMountPoint.h"
#include "Core/FileSystem/File.h"

PhysicalMountPoint::PhysicalMountPoint() {}

void PhysicalMountPoint::OnMount() {
	for (const auto & file : std::filesystem::directory_iterator(m_MountPoint)) {
		m_Files.push_back(file.path());
	}
}
void PhysicalMountPoint::OnUnMount() {
	m_Files.clear();
}

bool PhysicalMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool PhysicalMountPoint::HasFile(const std::filesystem::path file) {
	return std::filesystem::exists(m_MountPoint / file);
}
bool PhysicalMountPoint::HasDirectory(const std::filesystem::path directory) {
	return std::filesystem::is_directory(m_MountPoint / directory);
}

size_t PhysicalMountPoint::FileSize(const std::filesystem::path file) {
	if (HasFile(file)) {
		return std::filesystem::file_size(m_MountPoint / file);
	}
	return -1;
}

bool PhysicalMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	std::ofstream in(m_MountPoint / path, std::ofstream::ate | std::ofstream::binary | std::fstream::out);
	if (in.is_open()) {
		in.write(data, size);
		in.close();
		return true;
	}
	in.close();
	return false;
}
char * PhysicalMountPoint::ReadFile(const std::filesystem::path & path) {
	std::ifstream out(m_MountPoint / path, std::ifstream::ate | std::ifstream::binary);
	if (out.is_open()) {
		out.seekg(0, std::ios_base::end);
		int size = out.tellg();//Get file size in bits.
		out.seekg(0);
		char* data = new char[size];
		out.read((char*)data, size);
		return data;
	}
	out.close();
	return nullptr;
}

bool PhysicalMountPoint::CreateDirectory(const std::filesystem::path directory) {
	if (!HasDirectory(directory) || !HasFile(directory)) { // Check if src folder exists
		std::filesystem::create_directory(m_MountPoint / directory); // create src folder
		return true;
	}
	return false;
}
bool PhysicalMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	if (!HasFile(file)) {//Check is file not exist
		std::ofstream create;//Create file stream.
		create.open(m_MountPoint / file, std::ios::trunc);//open/create file.
		if (create.good()) {//Is open/create succsessfully.
			create.close();//Close file.
			return true;
		}
		else {
			create.close();//Close file.
			return false;
		}
	} else {
		return false;
	}
}

bool PhysicalMountPoint::RemoveFile(const std::filesystem::path file) {
	return std::filesystem::remove(m_MountPoint / file);
}
int PhysicalMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return std::filesystem::remove_all(m_MountPoint / directory);
}

PhysicalMountPoint::~PhysicalMountPoint() {}