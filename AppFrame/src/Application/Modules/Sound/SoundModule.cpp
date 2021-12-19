#include "SoundModule.h"
#include <alc.h>
#include <al.h>
#include <iostream>
#include "SoundSource.h"
#include "ResourceSound.h"
#include "ResourceManager/ResourceManager.h"

#define CASE_RETURN(err) case (err): return "##err"
const char* al_err_str(ALenum err) {
	//switch (err) {
		//CASE_RETURN(AL_NO_ERROR);
		if (err == AL_INVALID_NAME) {
			return "invalid name";
		} else if (err == AL_INVALID_ENUM) {
			return "invalid enum";
		}
		else if (err == AL_INVALID_VALUE) {
			return "invalid value";
		}
		else if (err == AL_INVALID_OPERATION) {
			return "invalid operation";
		}
		else if (err == AL_OUT_OF_MEMORY) {
			return "invalid memory";
		}
		//CASE_RETURN(AL_INVALID_NAME);
		//CASE_RETURN(AL_INVALID_ENUM);
		//CASE_RETURN(AL_INVALID_VALUE);
		//CASE_RETURN(AL_INVALID_OPERATION);
		//CASE_RETURN(AL_OUT_OF_MEMORY);
	//}
	return "unknown";
}
#undef CASE_RETURN

#define __al_check_error(file,line) \
    do { \
        ALenum err = alGetError(); \
        for(; err!=AL_NO_ERROR; err=alGetError()) { \
            std::cerr << "AL Error " << al_err_str(err) << " at " << file << ":" << line << std::endl; \
        } \
    }while(0)

#define al_check_error() \
    __al_check_error(__FILE__, __LINE__)

AppFrame::SoundModule::SoundModule() {

	device = alcOpenDevice(nullptr);
	if (device == nullptr) {
		std::cout << "Failed to get default sound device" << std::endl;
		return;
	}
	ALCcontext* context = alcCreateContext(device, nullptr);

	if (context == nullptr) {
		std::cout << "Failed to create sound context" << std::endl;
		return;
	}
	
	if (!alcMakeContextCurrent(context)) {
		std::cout << "Failed to make current sound context" << std::endl;
		return;
	}

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT")) {//If is multiple devices get all devices.
		name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
	}
	if (!name || alcGetError(device) != ALC_NO_ERROR) {//If is no multiple devices then get current device name.
		name = alcGetString(device, ALC_DEVICE_SPECIFIER);
	}
	if (name) {
		std::cout << "Default play devices: " << name << std::endl;
	} else {
		std::cout << "No device found" << std::endl;
	}

	GetAvailableSoundDevices();
	int i = 0;
	for (auto dev : m_Devices) {
		i++;
		std::cout << "Device " << i << ". " << dev << std::endl;
	}

	al_check_error();

	ResourceSound* resource = ResourceManager::GetInstace()->GetResource<ResourceSound>("mixkit-arcade-retro-game-over-213.wav");

	if (resource) {
		al_check_error();


		sound = new SoundSource();
		al_check_error();
		sound->SetSound(resource->Get());

		sound->SetGain(1);
		sound->SetPitch(1);
		sound->SetLoop(false);
		sound->SetPosition(0, 0, 0);
		sound->SetVelocity(0, 0, 0);
		al_check_error();

		sound->Play();
		al_check_error();
	}

}

AppFrame::SoundModule::~SoundModule() {
}

std::vector<std::string> AppFrame::SoundModule::GetAvailableSoundDevices() {
	m_Devices.clear();

	const ALCchar *devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	while (device && *device != '\0' && next && *next != '\0') {
		m_Devices.push_back(device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return m_Devices;
}

void AppFrame::SoundModule::OnAppInput(int x, int y, int action, int key) {
	if (key == 65) {
		sound->SetPitch(5);
		al_check_error();

		sound->Play();
	}
	if (key == 66) {
		sound->SetPitch(2);
		al_check_error();

		sound->Play();
	}

}