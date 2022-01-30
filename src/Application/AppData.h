#pragma once
#include "Core/Core.h"
#include <vector>
#include <string>

namespace AppFrame {
	class ENGINE_API AppData {
	public:
		void SetWindowWidth(float width);
		void SetWindowHeight(float height);
		void SetApplicationName(const char * name);
		void SetFPSLimit(int fps);

		float GetWindowWidth();
		float GetWindowHeight();
		std::string GetApplicationName();
		int GetFPSLimit();

		void SetStartupLang(const char* lang);
		void AddSupportLang(const char* lang);

		std::string GetStartupLang();
		std::vector<std::string>& GetSupportedLanguages();
	protected:
		float m_Width;
		float m_Height;

		std::string m_Name;
		std::string m_StatupLanguage;

		int m_FPS;

		std::vector<std::string> m_SupportedLanguages;
	};
}