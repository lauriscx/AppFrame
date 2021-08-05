#pragma once
#pragma warning( disable: 4251 )
#include "Core/Core.h"
#include <vector>

class ENGINE_API AppContext {
	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	void SetApplicationName(const char * name);
	void SetFPSLimit(int fps);
	void SetMemoryUsage(float memory);
	void SetLanguage(const char* language);

	void AddLanguage(const char* language);


private:
	float m_Width;
	float m_Height;

	const char * m_Name;

	int m_FPS;

	float m_MemoryUsage;

	const char * m_Language;
	std::vector<const char*> m_SupportedLanguages;
};