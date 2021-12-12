#pragma once
#include "Application/Modules/Module.h"
#include <alc.h>
#include <al.h>
#include "SoundSource.h"

namespace Engine {
	class SoundModule : public Module {
	public:
		SoundModule();
		virtual ~SoundModule();

		std::vector<std::string> GetAvailableSoundDevices();
		virtual void OnAppInput(int x, int y, int action, int key) override;
	private:
		std::vector<std::string> m_Devices;
		ALCdevice* device;
		SoundSource* sound;
	};
}