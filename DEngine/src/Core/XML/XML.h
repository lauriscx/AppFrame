#pragma once
#include "Core/Core.h"
#include "tinyxml2.h"

namespace XML {
	using namespace tinyxml2;

	inline XMLDocument* Parse(const std::string& text) {
		XMLDocument* doc = new XMLDocument();
		doc->Parse((const char*)text.c_str(), text.size());
		return doc;
	}
}