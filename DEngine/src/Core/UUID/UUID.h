#pragma once
#include "Core/Core.h"

class ENGINE_API UUID {
public:
	UUID();
	~UUID();
private:
	unsigned __int64 m_UUID;
};