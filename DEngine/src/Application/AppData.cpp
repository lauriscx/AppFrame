#include "AppData.h"

void AppData::SetWindowWidth(float width) {
	m_Width = width;
}

void AppData::SetWindowHeight(float height) {
	m_Height = height;
}

void AppData::SetApplicationName(const char * name) {
	m_Name = name;
}

void AppData::SetFPSLimit(int fps) {
	m_FPS = fps;
}

float AppData::GetWindowWidth() {
	return m_Width;
}

float AppData::GetWindowHeight() {
	return m_Height;
}

std::string AppData::GetApplicationName() {
	return m_Name;
}

int AppData::GetFPSLimit() {
	return m_FPS;
}

void AppData::SetStartupLang(const char * lang) {
	m_StatupLanguage = lang;
}

void AppData::AddSupportLang(const char * lang) {
	m_SupportedLanguages.push_back(lang);
}

std::string AppData::GetStartupLang() {
	return m_StatupLanguage;
}

std::vector<std::string>& AppData::GetSupportedLanguages() {
	return m_SupportedLanguages;
}
