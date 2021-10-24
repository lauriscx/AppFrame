#pragma once
#include "Core/Core.h"
#include <filesystem>
#include <map>

namespace Engine {
	class ENGINE_API VFS {
	public:
		bool Mount(const std::filesystem::path& _virtual, const std::filesystem::path& physical);
		bool Unmount(const std::filesystem::path& _virtual);
		bool MountExist(const std::filesystem::path& _virtual);

		bool GetPhysicPath(const std::filesystem::path& _virtual, std::filesystem::path* physic);

		std::filesystem::path GetPath(const std::filesystem::path& _virtual);

		static VFS& GetInstance() { static VFS s_Instance; return s_Instance; }
	private:
		std::map<std::filesystem::path, std::filesystem::path> m_MountPoints;
	};
}