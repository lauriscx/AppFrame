#pragma once

#include "DataTypes.h"
#include "Core/Core.h"

namespace Engine {
	class ENGINE_API Device {
	public:

		virtual const char* GetDeviceModel() const = 0;
		virtual const char* GetDeviceOS() const = 0;
		virtual const char* GetCPUModel() const = 0;
		virtual const char* GetGPUModel() const = 0;
		virtual const char* GetRegion() const = 0;

		virtual Currency::Values GetCurrency() const = 0;
		virtual Language::Values GetDeviceLanguage() const = 0;

		virtual int GetRAMMemory() const = 0;
		virtual int GetHardMemory() const = 0;
		virtual int GetScreenWidth() const = 0;
		virtual int GetScreenHeight() const = 0;
		virtual int GetInputType() const = 0;

		virtual ~Device() {}
	};
}