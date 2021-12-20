#include "ResourceTexture.h"  
#include "FileSystem/File.h"
#include "FileSystem/VFS/VFS.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AppFrame::ResourceTexture::ResourceTexture() { }

void * AppFrame::ResourceTexture::Get() {
	return m_data;
}

bool AppFrame::ResourceTexture::IsAvailable() {
	return m_data != nullptr;
}

bool AppFrame::ResourceTexture::Load(std::filesystem::path file) {
	/* Read file and parse wav data */
	File* _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		stbi_uc* l_data = stbi_load_from_memory((unsigned char*)_file->GetData(), _file->GetSize(), &m_Width, &m_Height, &m_Chanels, 0);
		m_data = l_data;
		if (l_data == nullptr) {
			stbi_image_free(l_data);
			return false;
		}
		delete _file;
		return true;
	}
	return false;
}

size_t AppFrame::ResourceTexture::GetMemoryUsage() {
	return sizeof(ResourceTexture) + (4 * m_Chanels * m_Width * m_Height);
}

AppFrame::ResourceTexture::~ResourceTexture() {
	if (m_data) {
		stbi_image_free(m_data);
	}
}