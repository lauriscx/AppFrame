#pragma once
#include "Core/ResourceManager/Resource.h"

class RecourceXML : public Resource {
public:
	RecourceXML();

	virtual bool IsAvailable() override;
	virtual bool Load(std::filesystem::path file) override;

	~RecourceXML();
};