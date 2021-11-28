#include "SoundModule.h"
#include <alc.h>
#include <iostream>

Engine::SoundModule::SoundModule() {

	ALCdevice* device = alcOpenDevice(nullptr);
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
		std::cout << "Devices: " << name << std::endl;
	} else {
		std::cout << "No device found" << std::endl;
	}
}

Engine::SoundModule::~SoundModule() {
}

int Engine::SoundModule::ID() {
	return 0;
}
