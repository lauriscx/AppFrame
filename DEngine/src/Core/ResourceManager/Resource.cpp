#include "Resource.h"

Resource::Resource() {}

bool Resource::IsAvailable() {
	return false;
}

bool Resource::Load(std::filesystem::path file) {
	return false;
}

Resource::~Resource() {}