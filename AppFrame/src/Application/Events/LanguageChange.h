#pragma once
#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace AppFrame {
	class LanguageChange : public BasicEvent {
	public:
		LanguageChange(const char* language) : m_language(language) {}
		static int Type() { return Events::LanguageChange; }
		static LanguageChange* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<LanguageChange*>(event);
			}
			return nullptr; 
		}
		virtual int GetType() override { return Type(); }
		const char* GetLanguage() { return m_language; }
	private:
		const char* m_language;
	};
}