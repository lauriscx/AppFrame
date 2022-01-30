#pragma once
#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace AppFrame {
	class Log : public BasicEvent {
	public:
		enum level {
			trace,
			debug,
			info,
			warn,
			error,
			fatal
		};
	public:
		Log(const char* module, const char* message, Log::level level) : m_Module(module), m_Message(message), m_Level(level) {}
		static int Type() { return Events::Log; }
		static Log* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<Log*>(event);
			}
			return nullptr;
		}
		virtual int GetType() override { return Type(); }
		const char* GetModule() { return m_Module; }
		const char* GetMsg() { return m_Message; }
		Log::level GetLevel() { return m_Level; };
	private:
		const char* m_Module;
		const char* m_Message;
		Log::level m_Level;
	};
}