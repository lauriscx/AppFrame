#pragma once
#include "Core/Core.h"
#include "Core/ResourceManager/Resource.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace AppFrame {
	class ResourceMesh : public Resource {
	public:
		ResourceMesh() { }
		ResourceMesh(std::filesystem::path file);

		const aiScene* Get();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual void OnRelease() override;
		virtual void OnLoad() override;

		virtual size_t GetMemoryUsage() override;

		virtual ~ResourceMesh();
	private:
		const aiScene* m_Resource;
		Assimp::Importer* m_Importer;
	};
}