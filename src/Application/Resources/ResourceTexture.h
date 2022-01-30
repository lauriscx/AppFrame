#pragma once
#include "Core/Core.h"
#include "Core/ResourceManager/Resource.h"

namespace AppFrame {
	class ResourceTexture : public Resource {
	public:
		ResourceTexture();

		void* Get();
		int GetWidth();
		int GetHeight();
		int GetChannels();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual size_t GetMemoryUsage() override;

		~ResourceTexture();
	private:
		unsigned char* m_data;
		int m_Width;
		int m_Height;
		int m_Channels;
	};
}