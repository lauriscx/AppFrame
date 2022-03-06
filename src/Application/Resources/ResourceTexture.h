#pragma once
#include "Core/Core.h"
#include "Core/ResourceManager/Resource.h"

namespace AppFrame {
	class ResourceTexture : public Resource {
	public:
		ResourceTexture(std::filesystem::path file);

		void* Get();
		int GetWidth();
		int GetHeight();
		int GetChannels();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual void OnRelease() override;
		virtual void OnLoad() override;

		virtual size_t GetMemoryUsage() override;

		~ResourceTexture();
	private:
		unsigned char* m_data;
		int m_Width;
		int m_Height;
		int m_Channels;
	};
}