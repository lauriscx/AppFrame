#include "Resource.h"

Resource::Resource() {}

bool Resource::IsAvailable() {
	return false;
}

bool Resource::Load(std::filesystem::path file) {
	return false;
}

void Resource::OnLoad() { }
void Resource::OnRelease() { }

size_t Resource::GetMemoryUsage() {
	return sizeof(this);
}

Resource::~Resource() {}