#include "Resource.h"

AppFrame::Resource::Resource() {}

bool AppFrame::Resource::IsAvailable() {
	return false;
}

bool AppFrame::Resource::Load(std::filesystem::path file) {
	return false;
}

void AppFrame::Resource::OnLoad() { }
void AppFrame::Resource::OnRelease() { }

size_t AppFrame::Resource::GetMemoryUsage() {
	return sizeof(this);
}

AppFrame::Resource::~Resource() {}