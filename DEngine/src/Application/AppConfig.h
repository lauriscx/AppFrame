#pragma once
#include "Core/Core.h"

class ENGINE_API AppConfig {
public:
	void virtual SetWindowWidth(float width);
	void virtual SetWindowHeight(float height);
	void virtual SetApplicationName(const char * name);
	void virtual SetFPSLimit(int fps);

private:
	float m_Width;
	float m_Height;

	const char * m_Name;

	int m_FPS;
};