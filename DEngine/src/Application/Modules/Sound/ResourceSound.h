#pragma once
#include "ResourceManager/Resource.h"

class ResourceSound : public Resource {
public:
	ResourceSound();

	//tinyxml2::XMLDocument* Get();

	virtual bool IsAvailable() override;
	virtual bool Load(std::filesystem::path file) override;

	virtual size_t GetMemoryUsage() override;

	virtual ~ResourceSound();
private:
	//Add resource.
};