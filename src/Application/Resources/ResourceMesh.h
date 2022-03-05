#pragma once
#include "Core/Core.h"
#include "Core/ResourceManager/Resource.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace AppFrame {
	class ResourceMesh : public Resource {
	public:

		ResourceMesh();

		const aiScene* Get();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual size_t GetMemoryUsage() override;

		~ResourceMesh();
	private:
		const aiScene* m_Resource;
		Assimp::Importer importer;
	};
}