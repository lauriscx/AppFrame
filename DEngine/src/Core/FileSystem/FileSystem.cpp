#include "FileSystem.h"
#include "DataTypes.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Core/Memory.h"

bool Engine::FileSystem::IsFileExists		(const std::filesystem::path& path) {
	return std::filesystem::exists(path);
}
bool Engine::FileSystem::IsDirectoryExist	(const std::filesystem::path& path) {
	return std::filesystem::is_directory(path);;
}
bool Engine::FileSystem::FileSize			(const std::filesystem::path& path, int64* size) {
	if (IsFileExists(path)) {
		*size = std::filesystem::file_size(path);
		return true;
	} else {
		return false;
	}
}

bool Engine::FileSystem::CreateDirectory	(const std::filesystem::path& path) {
	if (!IsDirectoryExist(path) || !IsFileExists(path)) { // Check if src folder exists
		std::filesystem::create_directory(path); // create src folder
		return true;
	}
	return false;
}
bool Engine::FileSystem::CreateFile			(const std::filesystem::path& path) {
	if (!IsFileExists(path)) {//Check is file not exist
		std::ofstream file;//Create file stream.
		file.open(path, std::ios::trunc);//open/create file.
		if (file.good()) {//Is open/create succsessfully.
			file.close();//Close file.
			return true;
		}
		else {
			file.close();//Close file.
			return false;
		}
	} else {
		return false;
	}
}

bool Engine::FileSystem::WriteTextFile		(const std::filesystem::path& path, const char* data) {
	std::ofstream file;

	file.open(path, std::ios::trunc);
	if (file.good()) {
		file << data << std::endl;

		file.close();
		return true;
	} else {
		file.close();
		return false;
	}
}
bool Engine::FileSystem::ReadTextFile		(const std::filesystem::path& path, const char* data) {
	std::ifstream file(path);

	if (file.good()) {//Check is file open successfully.
		std::stringstream _data;
		_data << file.rdbuf();//Read all text file.
		data = _data.str().c_str();//Set data.

		file.close();//close file.
		return true;
	} else {
		file.close();//close file.
		return false;
	}
}

bool Engine::FileSystem::WriteBinaryFile	(const std::filesystem::path& path, byte* data, size_t size) {
	std::ofstream file(path, std::ios::binary | std::ios::trunc);//Open file for writing.

	if (file.is_open()) {//Check is file open successfully.
		file.seekp(0);//Start write at begining of file.
		file.write((char*)data, size);//Write bytes.

		file.close();//close file
		return true;
	} else {
		file.close();//close file
		return false;
	}
}
bool Engine::FileSystem::ReadBinaryFile		(const std::filesystem::path& path, byte* data, size_t size) {
	std::ifstream file(path, std::ios::binary);//Open file for reading.

	if (file.good()) {//Check is file open successfully.
		file.seekg(0);//Start at begining.
		file.read((char*)data, size);//Read data to bytes variable to set size(point of file).
		file.close();//close file.
		return true;
	} else {
		file.close();//close file.
		return false;
	}
}

bool Engine::FileSystem::RemoveFile			(const std::filesystem::path& path) {
	return std::remove(path.string().c_str());
}

std::filesystem::path Engine::FileSystem::strip_root(const std::filesystem::path& path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/")
		return std::filesystem::path();
	else
		return strip_root(parent_path) += "/" + path.filename().string();
}

std::filesystem::path Engine::FileSystem::get_root	(const std::filesystem::path& path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/") {
		return path;
	} else {
		return get_root(parent_path);
	}
}
