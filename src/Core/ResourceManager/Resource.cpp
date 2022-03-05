#include "Resource.h"
#include "Core/ResourceManager/ResourceManager.h"

AppFrame::Resource::Resource() {}

bool AppFrame::Resource::IsAvailable() {
	return false;
}

bool AppFrame::Resource::Load(std::filesystem::path file) {
	if (!file.empty()) {
		m_File = file;
	}
	return false;
}

void AppFrame::Resource::OnLoad() { }
void AppFrame::Resource::OnRelease() { }

size_t AppFrame::Resource::GetMemoryUsage() {
	return sizeof(this);
}

AppFrame::Resource::~Resource() {
	if (!m_File.empty()) {
		AppFrame::ResourceManager::GetInstance()->ReleaseResource<Resource>(this);
	}
}