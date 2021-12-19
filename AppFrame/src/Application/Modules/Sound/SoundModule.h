#pragma once
#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"
#include "SoundSource.h"

class ALCdevice;
namespace Engine {
	class ENGINE_API SoundModule : public Module {
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