#include "AppConfig.h"
#include "Core/XML/XML.h"

AppConfig::AppConfig() {
	ParseConfigXML("C:/Users/Kosmosas/Desktop/xml.xml");
}

AppConfig::~AppConfig() {}

void AppConfig::ParseConfigXML(const char * path) {
	XML::XMLDocument Configuration;
	Configuration.LoadFile(path);
	XML::XMLElement* RootElement = Configuration.RootElement();
	if (RootElement) {
		XML::XMLElement* WindowConfig = RootElement->FirstChildElement("Window");
		if (WindowConfig) {
			SetApplicationName(WindowConfig->FirstChildElement("Name")->GetText());

			SetWindowWidth		(atoi(WindowConfig->FirstChildElement("Width"	)->GetText()));
			SetWindowHeight		(atoi(WindowConfig->FirstChildElement("Height"	)->GetText()));
			SetFPSLimit			(atoi(WindowConfig->FirstChildElement("FPS"		)->GetText()));
		}
		SetStartupLang(RootElement->FirstChildElement("StartupLanguage")->GetText());

		XML::XMLElement* SuportedLanguages = RootElement->FirstChildElement("SuportedLanguages");
		if (SuportedLanguages) {
			XML::XMLElement* SuportedLanguage = SuportedLanguages->FirstChildElement("Language");
			while (SuportedLanguage) {
				AddSupportLang(SuportedLanguage->GetText());
				SuportedLanguage = SuportedLanguage->NextSiblingElement("Language");
			}
		}
	}
}