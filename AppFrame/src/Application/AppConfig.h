#pragma once
#include "Core/Core.h"
#include <vector>
#include "AppData.h"

class ENGINE_API AppConfig : public AppData {
public:
	AppConfig();
	virtual ~AppConfig();
private:
	void ParseConfigXML(const char* path);
};