#include "ResourceSound.h"
#include <al.h>
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include <stdio.h>
#include <iostream>
#include "Application/Events/AppEvents.h"

AppFrame::ResourceSound::ResourceSound(std::filesystem::path file) {
	alGenBuffers(1, &m_ResourceHandle);
}

AppFrame::ResourceSound::ResourceSound() { }

unsigned int AppFrame::ResourceSound::Get() {
	return m_ResourceHandle;
}

AppFrame::ResourceSound::WAV_HEADER AppFrame::ResourceSound::GetInformation() {
	return m_Header;
}

char * AppFrame::ResourceSound::GetData() {
	return m_Data;
}

bool AppFrame::ResourceSound::IsAvailable() {
	return m_ResourceHandle;
}

bool AppFrame::ResourceSound::Load(std::filesystem::path file) {
	/* Read file and parse wav data */
	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {

		memcpy(&m_Header, _file->GetData(), sizeof(WAV_HEADER));
		std::string checkSring = (const char*)m_Header.Subchunk2ID;
		if (checkSring.size() > 0) {
			checkSring[4] = '\0';
			if (strcmp(checkSring.c_str(), "data") != 0) {
				ERROR("ResourceSound", "Not supported wav file format(it should be data) but is : %s\n" + checkSring.c_str());
				//fprintf(stderr, "Not supported wav file format(it should be data) but is: %s\n", checkSring.c_str());
				//delete _file;//It will erease all allocated memory inside(mean data which is char*).
				return false;
			}
		} else {
			ERROR("ResourceSound", "Not supported wav file format unknow format and error");
			//fprintf(stderr, "Not supported wav file format unknow format and error");
			return false;
		}

		m_Data = new char[m_Header.Subchunk2Size];
		memcpy(m_Data, _file->GetData() + sizeof(WAV_HEADER), m_Header.Subchunk2Size);

		alBufferData(m_ResourceHandle, AL_FORMAT_STEREO16, m_Data, m_Header.Subchunk2Size, m_Header.SamplesPerSec);

		//delete _file;//It will erease all allocated memory inside(mean data which is char*).
		
		ALenum err = alGetError();
		if (err != AL_NO_ERROR) {
			ERROR("ResourceSound", "OpenAL Error: %s\n" + alGetString(err));
			//fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
			return false;
		}
		return true;
	}
	return false;
}

size_t AppFrame::ResourceSound::GetMemoryUsage() {
	return size_t();
}

AppFrame::ResourceSound::~ResourceSound() {
	alDeleteBuffers(1, &m_ResourceHandle);
	m_ResourceHandle = 0;
	if (m_Data != nullptr) {
		delete[] m_Data;
	}
}

void AppFrame::ResourceSound::OnLoad() {

}

void AppFrame::ResourceSound::OnRelease() {
}