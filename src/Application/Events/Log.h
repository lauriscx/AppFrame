#pragma once
#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Core/EventSystem/EventManager.h"

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

#define TRACE(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, msg, Log::trace))
#define INFO(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, msg, Log::info))
#define WARNING(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::warn))
#define ERROR(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::error))
#define FATAL(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::fatal))
#define DEBUG(module, msg) EventManager::GetInstance()->SendEvent(new Log(module, msg, Log::debug))