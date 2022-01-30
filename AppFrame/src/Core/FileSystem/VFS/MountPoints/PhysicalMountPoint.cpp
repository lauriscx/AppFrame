#include "Core/FileSystem/VFS/MountPoints/PhysicalMountPoint.h"
#include "Core/FileSystem/File.h"
#include "Core/Asserts.h"

AppFrame::PhysicalMountPoint::PhysicalMountPoint() {}

void AppFrame::PhysicalMountPoint::OnMount() {
	for (const auto & file : std::filesystem::directory_iterator(m_MountPoint)) {
		m_Files.push_back(file.path());
	}
}
void AppFrame::PhysicalMountPoint::OnUnMount() {
	m_Files.clear();
}

bool AppFrame::PhysicalMountPoint::CreateMount(const std::filesystem::path file) {
	return false;
}

bool AppFrame::PhysicalMountPoint::HasFile(const std::filesystem::path file) {
	return std::filesystem::exists(GetRealPath(file));
}
bool AppFrame::PhysicalMountPoint::HasDirectory(const std::filesystem::path directory) {
	return std::filesystem::is_directory(GetRealPath(directory));
}

size_t AppFrame::PhysicalMountPoint::FileSize(const std::filesystem::path file) {
	if (HasFile(file)) {
		return std::filesystem::file_size(GetRealPath(file));
	}
	return -1;
}

bool AppFrame::PhysicalMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	std::ofstream in(GetRealPath(path), std::ofstream::ate | std::ofstream::binary | std::fstream::out);
	if (in.is_open()) {
		in.write(data, size);
		in.close();
		return true;
	}
	in.close();
	return false;
}
bool AppFrame::PhysicalMountPoint::WriteFile(File * file) {
	return WriteFile(file->GetPath(), file->GetData(), file->GetSize());
}
AppFrame::File* AppFrame::PhysicalMountPoint::ReadFile(const std::filesystem::path & path) {
	std::ifstream out(GetRealPath(path), std::ifstream::ate | std::ifstream::binary);
	if (out.is_open()) {
		out.seekg(0, std::ios_base::end);
		int size = out.tellg();//Get file size in bits.
		out.seekg(0);
		char* data = new char[size + 1];
		out.read((char*)data, size);
		data[size] = '\0';

		ASSERT(data != nullptr);

		File* CreatedFile = new File();
		CreatedFile->SetData(data);
		CreatedFile->SetPath(path);
		CreatedFile->SetSize(size);

		return CreatedFile;
	}
	out.close();
	return nullptr;
}

bool AppFrame::PhysicalMountPoint::CreateDirectory(const std::filesystem::path directory) {
	if (!HasDirectory(directory) || !HasFile(directory)) { // Check if src folder exists
		std::filesystem::create_directory(GetRealPath(directory)); // create src folder
		return true;
	}
	return false;
}
bool AppFrame::PhysicalMountPoint::CreateFile(const std::filesystem::path file, size_t size) {
	if (!HasFile(file)) {//Check is file not exist
		std::ofstream create;//Create file stream.
		create.open(GetRealPath(file), std::ios::trunc);//open/create file.
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

bool AppFrame::PhysicalMountPoint::RemoveFile(const std::filesystem::path file) {
	return std::filesystem::remove(GetRealPath(file));
}
int AppFrame::PhysicalMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return std::filesystem::remove_all(GetRealPath(directory));
}

AppFrame::PhysicalMountPoint::~PhysicalMountPoint() {}