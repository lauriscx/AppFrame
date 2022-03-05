#pragma once
#include "Core/Core.h"
#include <filesystem>


#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace AppFrame {
	class Resource {
	public:
		Resource();

		virtual bool IsAvailable();
		virtual bool Load(std::filesystem::path file);

		std::filesystem::path GetPath() { return m_File; }

		virtual void OnLoad();
		virtual void OnRelease();

		virtual size_t GetMemoryUsage();

		virtual ~Resource();
	protected:
		std::filesystem::path m_File;
	};
}