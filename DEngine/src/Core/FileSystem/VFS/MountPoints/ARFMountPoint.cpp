#include "ARFMountPoint.h"
#include <filesystem>
#include <fstream>
#include <iostream>

ARFMountPoint::ARFMountPoint()
{
}

void ARFMountPoint::OnMount() {
	m_ARF_File_data = new ARFFileHeader();
	m_ARF_File_data->COMVersion = 1;
	m_ARF_File_data->ConntentVersion = 0;
	//m_ARF_File_data->Folder = m_MountPoint;
	if (std::filesystem::exists(m_MountPoint)) {
		std::ifstream in(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
		if (in.is_open()) {
			/* Get from ARF file header/information about file */
			int SizeOfHeader = sizeof(ARFFileHeader);
			in.seekg(0);
			in.read((char*)m_ARF_File_data, sizeof(ARFFileHeader));

			/* Get virtual files entry points and vietual files info */
			in.seekg(SizeOfHeader);//Start read file immedetly after ARF file header info.
			int startsReadHeader = SizeOfHeader;//only used for printing.
			for (int i = 0; i < m_ARF_File_data->FilesCount; i++) {
				VirtualFileHeader* HeaderVFS = new VirtualFileHeader();
				std::cout << "Importing virtual file header size: " << sizeof(VirtualFileHeader) << " in location: " << startsReadHeader << "-" << startsReadHeader + sizeof(VirtualFileHeader) << std::endl;
				in.read((char*)HeaderVFS, sizeof(VirtualFileHeader));

				m_VirtualFiles.push_back(HeaderVFS);

				startsReadHeader = HeaderVFS->EndsAt;//Only used for printing
				in.seekg(HeaderVFS->EndsAt);
			}
			in.close();
		}
		in.close();
	}

}

void ARFMountPoint::OnUnMount() {
	m_VirtualFiles.erase(m_VirtualFiles.begin(), m_VirtualFiles.end());
}

bool ARFMountPoint::HasFile(const std::filesystem::path file)
{
	return false;
}

bool ARFMountPoint::HasDirectory(const std::filesystem::path directory)
{
	return false;
}

size_t ARFMountPoint::FileSize(const std::filesystem::path file) {
	for (auto _file : m_VirtualFiles) {
		if (file.compare(_file->Path) == 0) {
			return _file->EndsAt - _file->StartsAt;
		}
	}
	return -1;
}

bool ARFMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	std::ofstream out(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
	if (out.is_open()) {
		//Update ARF header file.
		m_ARF_File_data->FilesCount++;
		out.seekp(0);
		out.write((char*)m_ARF_File_data, sizeof(ARFFileHeader));
		/* Create virtual file header */
		VirtualFileHeader* header = new VirtualFileHeader();

		out.seekp(0, std::ios_base::end);//Get current ARF file size.
		int FileSize = out.tellp();
		out.seekp(FileSize);

		header->StartsAt = FileSize + sizeof(VirtualFileHeader);
		header->EndsAt = header->StartsAt + size;
		for (int i = 0; i < path.string().size(); i++) {
			header->Path[i] = path.string()[i];
		}

		out.write((char*)header, sizeof(VirtualFileHeader));
		m_VirtualFiles.push_back(header);

		//Write virtual file immedetly after virtual file header.
		out.seekp(header->StartsAt);

		out.write((char*)data, size);
		out.close();
		return true;
	}
	out.close();

	return false;
}

char* ARFMountPoint::ReadFile(const std::filesystem::path & path, size_t size) {
	for (auto file : m_VirtualFiles) {
		if (path.compare(file->Path) == 0) {
			std::ifstream in(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
			if (in.is_open()) {
				int fileSize = file->EndsAt - file->StartsAt;
				//std::cout << "Reading virtual file in location: " << file->StartsAt << "-" << file->EndsAt << " size: " << fileSize << std::endl;
				in.seekg(file->StartsAt);
				char* data = new char[fileSize];// (char*)malloc(fileSize);
				//char* data = (char*)malloc(fileSize);
				in.read(data, fileSize);
				in.close();
				return data;
			}
			in.close();
			nullptr;
		}
	}
	return nullptr;
}

bool ARFMountPoint::CreateDirectory(const std::filesystem::path directory)
{
	return false;
}

bool ARFMountPoint::CreateFile(const std::filesystem::path file)
{
	return false;
}

bool ARFMountPoint::RemoveFile(const std::filesystem::path file)
{
	return false;
}

int ARFMountPoint::RemoveDirectory(const std::filesystem::path directory)
{
	return 0;
}

ARFMountPoint::~ARFMountPoint() {
	delete m_ARF_File_data;
}
