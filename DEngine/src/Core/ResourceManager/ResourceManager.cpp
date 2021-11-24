#include "ResourceManager.h"
#include <filesystem>
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"

ResourceManager::ResourceManager() { }

void ResourceManager::ReleaseResource(std::filesystem::path path) {
}

ResourceManager::~ResourceManager() { }