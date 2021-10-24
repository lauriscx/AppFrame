#pragma once
#pragma warning( disable: 4251 )
#include "Core/Core.h"
#include <vector>
#include "AppData.h"

class ENGINE_API AppContext : public AppData {
public:
	AppContext();
	AppContext(AppData* data) {
		SetWindowWidth		(data->GetWindowWidth());
		SetWindowHeight		(data->GetWindowHeight());
		SetApplicationName	(data->GetApplicationName());
		SetFPSLimit			(data->GetFPSLimit());
		SetStartupLang		(data->GetStartupLang());
		m_SupportedLanguages = data->GetSupportedLanguages();
	}

	virtual ~AppContext();
};