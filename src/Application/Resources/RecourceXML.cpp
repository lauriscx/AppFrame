#include "RecourceXML.h"
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include <iostream>
#include "Core/XML/XML.h"
#include "Core/ResourceManager/ResourceManager.h"


AppFrame::RecourceXML::RecourceXML(std::filesystem::path file) : Resource(file) {
	//std::cout << "RecourceXML(std::filesystem::path file)" << std::endl;
}

tinyxml2::XMLDocument * AppFrame::RecourceXML::Get() {
	return m_Resource;
}

bool AppFrame::RecourceXML::IsAvailable() {
	return m_Resource != nullptr;
}

bool AppFrame::RecourceXML::Load(std::filesystem::path file) {

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

void AppFrame::RecourceXML::OnLoad() { }

size_t AppFrame::RecourceXML::GetMemoryUsage() {
	return sizeof(this) + sizeof(m_Resource);//Probably not correct.
}

AppFrame::RecourceXML::~RecourceXML() { }