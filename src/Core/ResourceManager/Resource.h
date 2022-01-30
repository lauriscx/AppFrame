#pragma once
#include "Core/Core.h"
#include <filesystem>

namespace AppFrame {
	class ENGINE_API Resource {
	public:
		Resource();

		virtual bool IsAvailable();
		virtual bool Load(std::filesystem::path file);

		virtual void OnLoad();
		virtual void OnRelease();

		virtual size_t GetMemoryUsage();

		virtual ~Resource();
	};
}