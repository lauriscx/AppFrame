#pragma once
#include "Core/Core.h"
#include "Core/Memory/DataTypes.h"

namespace AppFrame {
	class  Device {
	public:

		virtual const char* GetDeviceModel() { return nullptr; }
		virtual const char* GetDeviceOS() { return nullptr; }
		virtual const char* GetCPUModel() { return nullptr; }
		virtual const char* GetGPUModel() { return nullptr; }
		virtual const char* GetRegion() { return nullptr; }
		virtual unsigned int GetHardwareConcurrency() { return 0; }

		virtual const char* GetCurrency() { return nullptr; }
		virtual const char* GetDeviceLanguage() { return nullptr; }

		virtual int GetRAMMemory() { return 0; }
		virtual int GetHardMemory() { return 0; }
		virtual int GetScreenWidth() { return 0; }
		virtual int GetScreenHeight() { return 0; }
		virtual int GetInputType() { return 0; }

		/* Device functionality */
		virtual void Vibrate(int sec) {}
		virtual void ShowPopup(const char* title, const char* desc, const char* button1, const char* button2) {}
		virtual void AddNotification(const char* title, const char* desc, const char* image, const char* parameters) {}
		virtual void OnEventCallback(const char* functionAddress) {}

		virtual ~Device() {}
	};
}