#pragma once
#include "Core/Core.h"
#include "Core/ResourceManager/Resource.h"

namespace tinyxml2 {
	class XMLDocument;
}

namespace AppFrame {
	class RecourceXML : public Resource {
	public:
		RecourceXML(std::filesystem::path file);

		tinyxml2::XMLDocument* Get();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual void OnRelease() override;
		virtual void OnLoad() override;

		virtual size_t GetMemoryUsage() override;

		~RecourceXML();
	private:
		tinyxml2::XMLDocument* m_Resource;
	};
}