#include "SoundModule.h"
#include <iostream>

Engine::SoundModule::SoundModule() {

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
}

Engine::SoundModule::~SoundModule() {
}

std::vector<std::string> Engine::SoundModule::GetAvailableSoundDevices() {
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

int Engine::SoundModule::ID() {
	return 0;
}
