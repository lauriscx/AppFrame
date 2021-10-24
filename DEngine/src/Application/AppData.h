#pragma once
#include "Core/Core.h"
#include <vector>

class ENGINE_API AppData {
public:
	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	void SetApplicationName(const char * name);
	void SetFPSLimit(int fps);

	float GetWindowWidth();
	float GetWindowHeight();
	const char* GetApplicationName();
	int GetFPSLimit();

	void SetStartupLang(const char* lang);
	void AddSupportLang(const char* lang);

	const char* GetStartupLang();
	std::vector<std::string>& GetSupportedLanguages();
protected:
	float m_Width;
	float m_Height;

	const char * m_Name;
	const char * m_StatupLanguage;

	int m_FPS;

	std::vector<std::string> m_SupportedLanguages;
};

