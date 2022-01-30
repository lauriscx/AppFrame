#include "AppData.h"

void AppFrame::AppData::SetWindowWidth(float width) {
	m_Width = width;
}

void AppFrame::AppData::SetWindowHeight(float height) {
	m_Height = height;
}

void AppFrame::AppData::SetApplicationName(const char * name) {
	m_Name = name;
}

void AppFrame::AppData::SetFPSLimit(int fps) {
	m_FPS = fps;
}

float AppFrame::AppData::GetWindowWidth() {
	return m_Width;
}

float AppFrame::AppData::GetWindowHeight() {
	return m_Height;
}

std::string AppFrame::AppData::GetApplicationName() {
	return m_Name;
}

int AppFrame::AppData::GetFPSLimit() {
	return m_FPS;
}

void AppFrame::AppData::SetStartupLang(const char * lang) {
	m_StatupLanguage = lang;
}

void AppFrame::AppData::AddSupportLang(const char * lang) {
	m_SupportedLanguages.push_back(lang);
}

std::string AppFrame::AppData::GetStartupLang() {
	return m_StatupLanguage;
}

std::vector<std::string>& AppFrame::AppData::GetSupportedLanguages() {
	return m_SupportedLanguages;
}
