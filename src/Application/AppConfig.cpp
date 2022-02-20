#include "AppConfig.h"
#include "Core/XML/XML.h"
#include "Core/FileSystem/File.h"
#include "Core/FileSystem/VFS/VFS.h"

AppFrame::AppConfig::AppConfig() {
	ParseConfigXML("Configuration.xml");
}

AppFrame::AppConfig::~AppConfig() {}

void AppFrame::AppConfig::ParseConfigXML(const char * path) {
	tinyxml2::XMLDocument* Configuration;

	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(path);
	if (_file && _file->IsDataAvailable()) {
		Configuration = XML::Parse(_file->GetData());
		//delete _file;//It will erease all allocated memory inside(mean data which is char*).
	//}

	//if (Configuration->LoadFile(path) == tinyxml2::XML_SUCCESS) {
		tinyxml2::XMLElement* RootElement = Configuration->RootElement();
		if (RootElement) {
			tinyxml2::XMLElement* WindowConfig = RootElement->FirstChildElement("Window");
			if (WindowConfig) {
				SetApplicationName(WindowConfig->FirstChildElement("Name")->GetText());

				SetWindowWidth(atoi(WindowConfig->FirstChildElement("Width")->GetText()));
				SetWindowHeight(atoi(WindowConfig->FirstChildElement("Height")->GetText()));
				SetFPSLimit(atoi(WindowConfig->FirstChildElement("FPS")->GetText()));
			}
			SetStartupLang(RootElement->FirstChildElement("StartupLanguage")->GetText());

			tinyxml2::XMLElement* SuportedLanguages = RootElement->FirstChildElement("SuportedLanguages");
			if (SuportedLanguages) {
				tinyxml2::XMLElement* SuportedLanguage = SuportedLanguages->FirstChildElement("Language");
				while (SuportedLanguage) {
					AddSupportLang(SuportedLanguage->GetText());
					SuportedLanguage = SuportedLanguage->NextSiblingElement("Language");
				}
			}
		}
	} else {
		SetWindowWidth		(800);
		SetWindowHeight		(600);
		SetApplicationName	("Application");
		SetFPSLimit			(1);
		SetStartupLang		("EN");
		m_SupportedLanguages.push_back("EN");
	}
}