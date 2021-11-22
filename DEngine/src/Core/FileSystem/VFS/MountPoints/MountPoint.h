#pragma once
#include <filesystem>
#include <vector>

class MountPoint {
public:
	MountPoint();

	virtual bool SetMountPoint(std::filesystem::path mountPoint);
	virtual bool SetMountPriority(int priority);

	virtual bool CreateMount(const std::filesystem::path file);

	virtual void OnMount();
	virtual void OnUnMount();

	virtual bool HasFile(const std::filesystem::path file);
	virtual bool HasDirectory(const std::filesystem::path directory);

	virtual size_t FileSize(const std::filesystem::path file);

	virtual bool WriteFile(const std::filesystem::path& path, char* data, size_t size);
	virtual char* ReadFile(const std::filesystem::path& path);
	
	virtual bool CreateDirectory(const std::filesystem::path directory);
	virtual bool CreateFile(const std::filesystem::path file, size_t size);

	virtual bool RemoveFile(const std::filesystem::path file);
	virtual int RemoveDirectory(const std::filesystem::path directory);

	virtual std::filesystem::path GetPath();
	virtual int Priority();

	virtual ~MountPoint();

protected:
	std::filesystem::path m_MountPoint;
	std::vector<std::filesystem::path> m_Files;
	int m_Priority;
};