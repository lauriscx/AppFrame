#pragma once
#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"
#include "SoundSource.h"

class ALCdevice;
namespace AppFrame {
	class InputData;
	class SoundModule : public Module {
	public:
		SoundModule();
		virtual ~SoundModule();
		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnLateUpdate(float deltaTime) {}
		virtual void OnAppEvent(BasicEvent* event) {}
		virtual void OnStop() {}

		std::vector<std::string> GetAvailableSoundDevices();
		virtual void OnAppInput(const InputData& input) override;
	private:
		std::vector<std::string> m_Devices;
		ALCdevice* device;
		SoundSource* sound;
	};
}