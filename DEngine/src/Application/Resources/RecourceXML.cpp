#include "RecourceXML.h"
#include "FileSystem/VFS/VFS.h"
#include "FileSystem/File.h"
#include <iostream>

RecourceXML::RecourceXML() { }

bool RecourceXML::IsAvailable() {
	return false;
}

bool RecourceXML::Load(std::filesystem::path file) {
	File* _file = Engine::VFS::GetInstance()->ReadFile(file);
	std::string text = _file->GetData();
	std::cout << "Loaded XML file " << text << std::endl;
	return false;
}

RecourceXML::~RecourceXML() { }