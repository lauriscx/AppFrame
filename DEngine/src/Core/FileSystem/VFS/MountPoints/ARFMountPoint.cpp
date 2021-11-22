#include "ARFMountPoint.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Asserts.h"

char ARFMountPoint::ARF_Version = 1;

ARFMountPoint::ARFMountPoint() {}

void ARFMountPoint::OnMount() {
	m_ARF_File_data = new ARFFileHeader();
	m_ARF_File_data->Version = ARF_Version;
	m_ARF_File_data->ConntentVersion = 0;
	//m_ARF_File_data->Folder = m_MountPoint;
	if (std::filesystem::exists(m_MountPoint)) {
		std::ifstream in(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
		if (in.is_open()) {
			/* Get from ARF file header/information about file */
			int SizeOfHeader = sizeof(ARFFileHeader);
			in.seekg(0);
			in.read((char*)m_ARF_File_data, sizeof(ARFFileHeader));

			ASSERT(strlen(m_ARF_File_data->Name) > 0);
			ASSERT(strcmp(m_ARF_File_data->Format, "ARFX") == 0);
			ASSERT(ARF_Version == m_ARF_File_data->Version);

			/* Get virtual files entry points and vietual files info */
			in.seekg(SizeOfHeader);//Start read file immedetly after ARF file header info.
			//int startsReadHeader = SizeOfHeader;//only used for printing.
			for (int i = 0; i < m_ARF_File_data->FilesCount; i++) {
				VirtualFileHeader* HeaderVFS = new VirtualFileHeader();
				//std::cout << "Importing virtual file header size: " << sizeof(VirtualFileHeader) << " in location: " << startsReadHeader << "-" << startsReadHeader + sizeof(VirtualFileHeader) << std::endl;
				in.read((char*)HeaderVFS, sizeof(VirtualFileHeader));

				m_VirtualFiles.push_back(HeaderVFS);

				//startsReadHeader = HeaderVFS->EndsAt;//Only used for printing
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

bool ARFMountPoint::CreateMount(const std::filesystem::path file) {
	if (!std::filesystem::exists(file)) {
		std::ofstream out(file, std::ifstream::ate | std::ifstream::binary);
		if (out.is_open()) {
			ARFFileHeader header;
			header.Version = ARF_Version;
			header.ConntentVersion = 0;

			strncpy_s(header.Format	, "ARFX", sizeof(header.Format) - 1);

			strncpy_s(header.Path	, file.string().c_str()					, sizeof(header.Path	) - 1);
			strncpy_s(header.Folder	, file.parent_path().string().c_str()	, sizeof(header.Folder	) - 1);
			strncpy_s(header.Name	, file.filename().string().c_str()		, sizeof(header.Name	) - 1);

			UpdateARFHeader(&out, 0, &header);
			out.close();
			return true;
		}
		out.close();
	}
	return false;
}

bool ARFMountPoint::HasFile(const std::filesystem::path file) {
	for (auto _file : m_VirtualFiles) {
		if (!_file->Deleted && file.compare(_file->Path) == 0) {
			return true;
		}
	}
	return false;
}
bool ARFMountPoint::HasDirectory(const std::filesystem::path directory) {

	return false;
}
size_t ARFMountPoint::FileSize(const std::filesystem::path file) {
	for (auto _file : m_VirtualFiles) {
		if (!_file->Deleted && file.compare(_file->Path) == 0) {
			return _file->Size;
		}
	}
	return -1;
}

bool ARFMountPoint::WriteFile(const std::filesystem::path & path, char * data, size_t size) {
	if (!HasFile(path)) {
		std::ofstream out(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
		if (out.is_open()) {
			UpdateARFHeader(&out, 1, m_ARF_File_data);
			VirtualFileHeader* header = CreateVirtualFileHeader(&out, size, path);
			WriteVirtualFileHeader(&out, header);
			WriteVirtualFile(&out, data, header);
			out.close();
			return true;
		}
		out.close();
	}
	return false;
}
char* ARFMountPoint::ReadFile(const std::filesystem::path & path, size_t size) {
	for (auto file : m_VirtualFiles) {
		if (!file->Deleted && path.compare(file->Path) == 0) {/* Do not use HasFile in this case */
			std::ifstream in(m_MountPoint, std::ifstream::ate | std::ifstream::binary);

			if (in.is_open()) {
				char* data = ReadVirtualFile(&in, file);
				in.close();
				return data;
			}

			in.close();
			nullptr;
		}
	}
	return nullptr;
}

bool ARFMountPoint::CreateDirectory(const std::filesystem::path directory) {
	return false;
}
bool ARFMountPoint::CreateFile(const std::filesystem::path file) {
	return false;
}

bool ARFMountPoint::RemoveFile(const std::filesystem::path file) {
	for (auto _file : m_VirtualFiles) {
		if (file.compare(_file->Path) == 0 && !_file->Deleted) {
			std::ofstream out(m_MountPoint, std::ifstream::ate | std::ifstream::binary);
			if (out.is_open()) {
				_file->Deleted = true;

				UpdateVirtualFileHeader(&out, _file, m_ARF_File_data, -1);//Update system than file was deleted. File still exis but it is not available anymore.
			}
			out.close();
			return true;
		}
	}
	return false;
}
int ARFMountPoint::RemoveDirectory(const std::filesystem::path directory) {
	return 0;
}

ARFMountPoint::~ARFMountPoint() {
	delete m_ARF_File_data;
}

void ARFMountPoint::UpdateARFHeader(std::ofstream* out, int FilesAdded, ARFFileHeader* header) {
	//Update ARF header file.
	header->FilesCount += FilesAdded;
	header->ConntentVersion++;
	out->seekp(0);
	out->write((char*)header, sizeof(ARFFileHeader));
}
ARFMountPoint::VirtualFileHeader* ARFMountPoint::CreateVirtualFileHeader(std::ofstream * out, uint32_t size, std::filesystem::path path) {
	/* Create virtual file header */
	VirtualFileHeader* header = new VirtualFileHeader();

	out->seekp(0, std::ios_base::end);//Get current ARF file size.
	int FileSize = out->tellp();
	out->seekp(FileSize);

	header->StartsAt = FileSize + sizeof(VirtualFileHeader);
	header->EndsAt = header->StartsAt + size;
	header->Size = size;

	strncpy_s(header->Path		, path.string().c_str()					, sizeof(header->Path	) - 1);
	strncpy_s(header->Folder	, path.parent_path().string().c_str()	, sizeof(header->Folder	) - 1);
	strncpy_s(header->Name		, path.filename().string().c_str()		, sizeof(header->Name	) - 1);

	/*for (int i = 0; i < path.string().size(); i++) {
		header->Path[i] = path.string()[i];
	}*/
	return header;
}
void ARFMountPoint::WriteVirtualFileHeader(std::ofstream * out, VirtualFileHeader * header) {
	out->write((char*)header, sizeof(VirtualFileHeader));
	m_VirtualFiles.push_back(header);//Save localy writed file header.
}
void ARFMountPoint::UpdateVirtualFileHeader(std::ofstream * out, VirtualFileHeader * header, ARFFileHeader * ARF_header, int addedFiles) {
	out->seekp(header->StartsAt - sizeof(VirtualFileHeader));//Update virtual file header find where stars virtual file then step back in size of header.
	out->write((char*)header, sizeof(VirtualFileHeader));//Write virtual file.
	UpdateARFHeader(out, addedFiles, ARF_header);//Update ARF header
}
void ARFMountPoint::WriteVirtualFile(std::ofstream * out, char * data, VirtualFileHeader* header) {
	//Write virtual file immedetly after virtual file header.
	out->seekp(header->StartsAt);//Set start position in ARF file.
	out->write((char*)data, header->Size);//Write virtual file.
}
char * ARFMountPoint::ReadVirtualFile(std::ifstream * in, VirtualFileHeader * header) {
	in->seekg(header->StartsAt);//Set read position in ARF file.
	char* data = new char[header->Size];//Create buffer for readed data.
	in->read(data, header->Size);//Reada virtual file data.
	return data;
}