#include "ResourceTexture.h"  
#include "Core/FileSystem/File.h"
#include "Core/FileSystem/VFS/VFS.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AppFrame::ResourceTexture::ResourceTexture() { }

void * AppFrame::ResourceTexture::Get() {
	return m_data;
}

int AppFrame::ResourceTexture::GetWidth() {
	return m_Width;
}
int AppFrame::ResourceTexture::GetHeight() {
	return m_Height;
}
int AppFrame::ResourceTexture::GetChannels() {
	return m_Channels;
}

bool AppFrame::ResourceTexture::IsAvailable() {
	return m_data != nullptr;
}

bool AppFrame::ResourceTexture::Load(std::filesystem::path file) {
	/* Read file and parse png data */
	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		//stbi_set_flip_vertically_on_load();//for openGL
		//stbi_set_flip_vertically_on_load(1);
		stbi_uc* l_data = stbi_load_from_memory((unsigned char*)_file->GetData(), _file->GetSize(), &m_Width, &m_Height, &m_Channels, 0);
		m_data = l_data;
		stbi__vertical_flip(m_data, m_Width, m_Height, m_Channels);
		if (l_data == nullptr) {
			stbi_image_free(l_data);
			return false;
		}
		//delete _file;
		return true;
	}
	return false;
}

size_t AppFrame::ResourceTexture::GetMemoryUsage() {
	return sizeof(ResourceTexture) + (m_Channels * m_Width * m_Height);
}

AppFrame::ResourceTexture::~ResourceTexture() {
	if (m_data) {
		stbi_image_free(m_data);
	}
}