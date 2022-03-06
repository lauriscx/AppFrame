#include "Application/Resources/ResourceMesh.h"
#include "Core/ResourceManager/ResourceManager.h"

AppFrame::ResourceMesh::ResourceMesh(std::filesystem::path file) : Resource(file) { }

const aiScene* AppFrame::ResourceMesh::Get() {
	return m_Resource;
}

bool AppFrame::ResourceMesh::IsAvailable() {
	return m_Resource != nullptr;
}

bool AppFrame::ResourceMesh::Load(std::filesystem::path file) {
	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		m_Importer = new Assimp::Importer();
		m_Resource = m_Importer->ReadFileFromMemory(_file->GetData(), _file->GetSize(), aiProcess_FlipUVs);
		if (m_Resource) {
			return true;
		}
	}
	return false;
}

void AppFrame::ResourceMesh::OnRelease() {
	if (m_Importer) {
		delete m_Importer;
	}
}

void AppFrame::ResourceMesh::OnLoad() { }

size_t AppFrame::ResourceMesh::GetMemoryUsage() {
	return sizeof(ResourceMesh);
}

AppFrame::ResourceMesh::~ResourceMesh() { }