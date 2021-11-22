#pragma once
#include "MountPoint.h"
#include "Core.h"

class ARFMountPoint : public MountPoint {
public:
	ARFMountPoint();

	virtual void OnMount() override;
	virtual void OnUnMount() override;

	virtual bool CreateMount(const std::filesystem::path file) override;

	virtual bool HasFile(const std::filesystem::path file) override;
	virtual bool HasDirectory(const std::filesystem::path directory) override;

	virtual size_t FileSize(const std::filesystem::path file) override;

	virtual bool WriteFile(const std::filesystem::path& path, char* data, size_t size) override;
	virtual char* ReadFile(const std::filesystem::path& path) override;

	virtual bool CreateDirectory(const std::filesystem::path directory) override;
	virtual bool CreateFile(const std::filesystem::path file, size_t size) override;

	virtual bool RemoveFile(const std::filesystem::path file) override;
	virtual int RemoveDirectory(const std::filesystem::path directory) override;

	virtual ~ARFMountPoint();

public:
	struct ARFFileHeader {
		char		Version = 1;
		uint32_t	FilesCount = 0;
		uint32_t	ConntentVersion = 0;
		char		Format[5] = "ARFX";
		char		Path[150];
		char		Folder[100];
		char		Name[50];
		char		Reserver[1000];//Used for reserving memory for future features.
	};
	struct VirtualFileHeader {
		char		Path[150];
		char		Folder[100];
		char		Name[50];
		uint32_t	StartsAt = 0;
		uint32_t	EndsAt = 0;
		uint32_t	Size = 0;
		bool		Deleted = false;
		char		Reserver[500];//Used for reserving memory for future features.
	};

	static char ARF_Version;
private:
	ARFFileHeader* m_ARF_File_data;
	std::vector<VirtualFileHeader*> m_VirtualFiles;

private:/* Helper functions */
	void UpdateARFHeader(std::ofstream* out, int FilesAdded, ARFFileHeader* header);
	VirtualFileHeader* CreateVirtualFileHeader(std::ofstream* out, uint32_t size, std::filesystem::path path);
	void WriteVirtualFileHeader(std::ofstream* out, VirtualFileHeader* header);
	void UpdateVirtualFileHeader(std::ofstream* out, VirtualFileHeader* header, ARFFileHeader* ARF_header, int addedFiles);
	void WriteVirtualFile(std::ofstream* out, char* data, VirtualFileHeader* header);
	char* ReadVirtualFile(std::ifstream* in, VirtualFileHeader* header);
};