#pragma once
#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class LanguageChange : public BasicEvent {
	public:
		LanguageChange(const char* language) : m_language(language) {}
		static int Type() { return Events::LanguageChange; }
		virtual int GetType() override { return Type(); }
		const char* GetLanguage() { return m_language; }
	private:
		const char* m_language;
	};
}