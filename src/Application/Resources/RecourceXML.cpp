#include "RecourceXML.h"
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include <iostream>
#include "Core/XML/XML.h"
#include "Core/ResourceManager/ResourceManager.h"


AppFrame::RecourceXML::RecourceXML() { }

tinyxml2::XMLDocument * AppFrame::RecourceXML::Get() {
	return m_Resource;
}

bool AppFrame::RecourceXML::IsAvailable() {
	return m_Resource != nullptr;
}

bool AppFrame::RecourceXML::Load(std::filesystem::path file) {
	AppFrame::Resource::Load(file);

	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		m_Resource = XML::Parse(_file->GetData());
		//delete _file;//It will erease all allocated memory inside(mean data which is char*).
		return true;
	}
	return false;
}

void AppFrame::RecourceXML::OnRelease() {
	if (m_Resource) {
		delete m_Resource;
	}
}

size_t AppFrame::RecourceXML::GetMemoryUsage() {
	return sizeof(this) + sizeof(m_Resource);//Probably not correct.
}

AppFrame::RecourceXML::~RecourceXML() { 
	if (!m_File.empty()) {
		AppFrame::ResourceManager::GetInstance()->ReleaseResource<RecourceXML>(this);
	}
}