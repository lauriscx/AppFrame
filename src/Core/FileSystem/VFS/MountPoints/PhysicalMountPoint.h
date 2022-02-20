#pragma once
#include "Core/Core.h"
#include "MountPoint.h"

namespace AppFrame {
	class File;
	class PhysicalMountPoint : public MountPoint {
	public:
		PhysicalMountPoint();

		virtual void OnMount() override;
		virtual void OnUnMount() override;

		virtual bool CreateMount(const std::filesystem::path file) override;

		virtual bool HasFile(const std::filesystem::path file) override;
		virtual bool HasDirectory(const std::filesystem::path directory) override;

		virtual size_t FileSize(const std::filesystem::path file) override;

		virtual bool WriteFile(const std::filesystem::path& path, char* data, size_t size) override;
		virtual bool WriteFile(File* file) override;
		virtual File* ReadFile(const std::filesystem::path& path) override;

		virtual bool CreateDirectory(const std::filesystem::path directory) override;
		virtual bool CreateFile(const std::filesystem::path file, size_t size) override;

		virtual bool RemoveFile(const std::filesystem::path file) override;
		virtual int RemoveDirectory(const std::filesystem::path directory) override;

		virtual std::vector<std::filesystem::directory_entry> Directories(std::filesystem::path dir = "") override;

		virtual ~PhysicalMountPoint();
	};
}