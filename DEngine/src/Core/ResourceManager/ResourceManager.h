#pragma once
#include "Resource.h"
#include <vector>
#include <FileSystem>
#include <map>

class ResourceManager {
public:
	ResourceManager();

	template <typename T>
	T* GetResource(std::filesystem::path path);
	void ReleaseResource(std::filesystem::path path);

	virtual ~ResourceManager();

private:
	std::map<size_t, Resource*> m_Resource;

};