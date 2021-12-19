#include "ResourceSound.h"
#include <al.h>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"
#include <stdio.h>
#include <iostream>

ResourceSound::ResourceSound() {
	alGenBuffers(1, &m_ResourceHandle);
}

unsigned int ResourceSound::Get() {
	return m_ResourceHandle;
}

ResourceSound::WAV_HEADER ResourceSound::GetInformation() {
	return m_Header;
}

char * ResourceSound::GetData() {
	return m_Data;
}

bool ResourceSound::IsAvailable() {
	return m_ResourceHandle;
}

bool ResourceSound::Load(std::filesystem::path file) {
	/* Read file and parse wav data */
	File* _file = Engine::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {

		memcpy(&m_Header, _file->GetData(), sizeof(WAV_HEADER));
		std::string checkSring = (const char*)m_Header.Subchunk2ID;
		if (checkSring.size() > 0) {
			checkSring[4] = '\0';
			if (strcmp(checkSring.c_str(), "data") != 0) {
				fprintf(stderr, "Not supported wav file format(it should be data) but is: %s\n", checkSring.c_str());
				delete _file;//It will erease all allocated memory inside(mean data which is char*).
				return false;
			}
		} else {
			fprintf(stderr, "Not supported wav file format unknow format and error");
			return false;
		}

		m_Data = new char[m_Header.Subchunk2Size];
		memcpy(m_Data, _file->GetData() + sizeof(WAV_HEADER), m_Header.Subchunk2Size);

		alBufferData(m_ResourceHandle, AL_FORMAT_STEREO16, m_Data, m_Header.Subchunk2Size, m_Header.SamplesPerSec);

		delete _file;//It will erease all allocated memory inside(mean data which is char*).
		
		ALenum err = alGetError();
		if (err != AL_NO_ERROR) {
			fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
			return false;
		}
		return true;
	}
	return false;
}

size_t ResourceSound::GetMemoryUsage() {
	return size_t();
}

ResourceSound::~ResourceSound() {
	alDeleteBuffers(1, &m_ResourceHandle);
	m_ResourceHandle = 0;
	if (m_Data != nullptr) {
		delete[] m_Data;
	}
}
