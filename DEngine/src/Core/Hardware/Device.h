#pragma once

#include "Core/Memory/DataTypes.h"
#include "Core/Core.h"

namespace Engine {
	class ENGINE_API Device {
	public:

		virtual const char* GetDeviceModel() const = 0;
		virtual const char* GetDeviceOS() const = 0;
		virtual const char* GetCPUModel() const = 0;
		virtual const char* GetGPUModel() const = 0;
		virtual const char* GetRegion() const = 0;

		virtual const char* GetCurrency() const = 0;
		virtual const char* GetDeviceLanguage() const = 0;

		virtual int GetRAMMemory() const = 0;
		virtual int GetHardMemory() const = 0;
		virtual int GetScreenWidth() const = 0;
		virtual int GetScreenHeight() const = 0;
		virtual int GetInputType() const = 0;

		/* Device functionality */
		virtual void Vibrate(int sec) const = 0;
		virtual void ShowPopup(const char* title, const char* desc, const char* button1, const char* button2) const = 0;
		virtual void AddNotification(const char* title, const char* desc, const char* image, const char* parameters) const = 0;
		virtual void OnEventCallback(const char* functionAddress) const = 0;

		virtual ~Device() {}
	};
}