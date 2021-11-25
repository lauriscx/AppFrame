#include "AppConfig.h"
#include "Core/XML/XML.h"

AppConfig::AppConfig() {
	ParseConfigXML("C:/Users/Kosmosas/Desktop/xml.xml");
}

AppConfig::~AppConfig() {}

void AppConfig::ParseConfigXML(const char * path) {
	tinyxml2::XMLDocument Configuration;
	if (Configuration.LoadFile(path) == tinyxml2::XML_SUCCESS) {
		tinyxml2::XMLElement* RootElement = Configuration.RootElement();
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
		SetWindowWidth		(600);
		SetWindowHeight		(800);
		SetApplicationName	("Application");
		SetFPSLimit			(60);
		SetStartupLang		("EN");
		m_SupportedLanguages.push_back("EN");
	}
}