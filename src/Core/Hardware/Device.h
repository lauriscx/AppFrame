#pragma once
#include "Core/Core.h"
#include "Core/Memory/DataTypes.h"
#include <string>

namespace AppFrame {
	class Device {
	public:

		/* Return empty string then canceled or failed */
		static std::string OpenFile(const char* filter = "Text file (*.txt)\0*.txt\0");
		static std::string SaveFile(const char* filter = "Text file (*.txt)\0*.txt\0");

		virtual const char* GetDeviceModel();
		virtual const char* GetDeviceOS();
		virtual const char* GetCPUModel();
		virtual const char* GetGPUModel();
		virtual const char* GetRegion();
		virtual unsigned int GetHardwareConcurrency();

		virtual const char* GetCurrency();
		virtual const char* GetDeviceLanguage();

		virtual int GetRAMMemory();
		virtual int GetHardMemory();
		virtual int GetScreenWidth();
		virtual int GetScreenHeight();
		virtual int GetInputType();

		/* Device functionality */
		virtual void Vibrate(int sec);
		virtual void ShowPopup(const char* title, const char* desc, const char* button1, const char* button2);
		virtual void AddNotification(const char* title, const char* desc, const char* image, const char* parameters);
		virtual void OnEventCallback(const char* functionAddress);

		virtual ~Device() {}
	};
}