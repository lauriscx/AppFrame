#pragma once
#include "Core/Core.h"
#include <vector>
#include "AppData.h"

namespace AppFrame {
	class ENGINE_API AppContext : public AppData {
	public:
		AppContext() {}
		AppContext(AppData * data) {
			if (data) {
				SetWindowWidth(data->GetWindowWidth());
				SetWindowHeight(data->GetWindowHeight());
				SetApplicationName(data->GetApplicationName().c_str());
				SetFPSLimit(data->GetFPSLimit());
				SetStartupLang(data->GetStartupLang().c_str());
				m_SupportedLanguages = data->GetSupportedLanguages();
			}
			else {
				SetWindowWidth(600);
				SetWindowHeight(800);
				SetApplicationName("Application");
				SetFPSLimit(60);
				SetStartupLang("EN");
				m_SupportedLanguages.push_back("EN");
			}
		}

		virtual ~AppContext() {}
	};
}