#include "ResourceSound.h"
#include <al.h>

ResourceSound::ResourceSound() {}

bool ResourceSound::IsAvailable() {
	return false;
}

bool ResourceSound::Load(std::filesystem::path file) {
	return false;
}

size_t ResourceSound::GetMemoryUsage() {
	return size_t();
}

ResourceSound::~ResourceSound() {}