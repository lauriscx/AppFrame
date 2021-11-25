#include "RecourceXML.h"
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"
#include <iostream>
#include "Core/XML/XML.h"

RecourceXML::RecourceXML() { }

tinyxml2::XMLDocument * RecourceXML::Get() {
	return m_Resource;
}

bool RecourceXML::IsAvailable() {
	return m_Resource != nullptr;
}

bool RecourceXML::Load(std::filesystem::path file) {
	File* _file = Engine::VFS::GetInstance()->ReadFile(file);
	if (_file->IsDataAvailable()) {
		m_Resource = XML::Parse(_file->GetData());
	}
	delete _file;//It will erease all allocated memory inside(mean data which is char*).
	return true;
}

size_t RecourceXML::GetMemoryUsage() {
	return sizeof(this) + sizeof(m_Resource);//Probably not correct.
}

RecourceXML::~RecourceXML() {
	delete m_Resource;
}