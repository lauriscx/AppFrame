#pragma once
#include "Core/Core.h"
#include "tinyxml2.h"

namespace XML {
	//using namespace tinyxml2;

	inline tinyxml2::XMLDocument* Parse(const std::string& text) {
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->Parse((const char*)text.c_str(), text.size());
		return doc;
	}
}