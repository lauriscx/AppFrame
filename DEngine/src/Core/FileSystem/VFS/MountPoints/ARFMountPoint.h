#pragma once
#include "MountPoint.h"

class ARFMountPoint : public MountPoint {
public:
	ARFMountPoint();

	virtual void OnMount() override;
	virtual void OnUnMount() override;

	virtual bool HasFile(const std::filesystem::path file) override;
	virtual bool HasDirectory(const std::filesystem::path directory) override;
	virtual size_t FileSize(const std::filesystem::path file) override;

	virtual bool WriteFile(const std::filesystem::path& path, char* data, size_t size);
	virtual char* ReadFile(const std::filesystem::path& path, size_t size);

	virtual bool CreateDirectory(const std::filesystem::path directory) override;
	virtual bool CreateFile(const std::filesystem::path file) override;
	virtual bool RemoveFile(const std::filesystem::path file) override;
	virtual int RemoveDirectory(const std::filesystem::path directory) override;

	virtual ~ARFMountPoint();

public:
	struct ARFFileHeader {
		uint32_t	FilesCount = 0;
		char		Format[5] = "ARF";
		char		COMVersion = 0;
		int			ConntentVersion = 0;
		char		Name[50];
		char		Folder[100];
		char		Reserver[1000];//Used for reserving memory for future features.
	};
	struct VirtualFileHeader {
		char		Path[150];
		char		Folder[100];
		char		Name[50];
		uint32_t	StartsAt;
		uint32_t	EndsAt;
		char		Reserver[500];//Used for reserving memory for future features.
	};

private:
	ARFFileHeader* m_ARF_File_data;
	std::vector<VirtualFileHeader*> m_VirtualFiles;
};