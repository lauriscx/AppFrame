#include "Application/Resources/ResourceMesh.h"

#include <AppFrame.h>

#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include "Core/ResourceManager/ResourceManager.h"

AppFrame::ResourceMesh::ResourceMesh() {}

const aiScene* AppFrame::ResourceMesh::Get() {
	return m_Resource;
}

bool AppFrame::ResourceMesh::IsAvailable() {
	return m_Resource != nullptr;
}

bool AppFrame::ResourceMesh::Load(std::filesystem::path file) {
	AppFrame::Resource::Load(file);

	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		m_Resource = importer.ReadFileFromMemory(_file->GetData(), _file->GetSize(), aiProcess_FlipUVs);

		//ERROR("Graphic", importer.GetErrorString());

		//m_Resource = importer.ReadFile("C:/Users/Kosmosas/Desktop/Application/model.dae", aiProcess_Triangulate);
		if (m_Resource) {
			//m_Resource->mMeshes;
			//m_Resource->mNumMeshes;
			//m_Resource->mNumMaterials;
			return true;
		}
	}
	return false;
}

size_t AppFrame::ResourceMesh::GetMemoryUsage() {
	return sizeof(ResourceMesh);
}

AppFrame::ResourceMesh::~ResourceMesh() { 
	if (!m_File.empty()) {
		AppFrame::ResourceManager::GetInstance()->ReleaseResource<ResourceMesh>(this);
	}
}