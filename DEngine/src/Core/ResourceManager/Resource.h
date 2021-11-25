#pragma once
#include <filesystem>

class Resource {
public:
	Resource();

	virtual bool IsAvailable();
	virtual bool Load(std::filesystem::path file);

	virtual void OnLoad();
	virtual void OnRelease();

	virtual size_t GetMemoryUsage();

	virtual ~Resource();
};