#pragma once
#include "Core/EventSystem/EventManager.h"
#include "Application/Events/Log.h"

#define TRACE(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::trace))
#define INFO(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::info))
#define WARNING(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::warn))
#define ERROR(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::error))
#define FATAL(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, (std::string("\n[FILE] ") + std::string(__FILE__) + std::string("\n[LINE] ") + std::to_string(__LINE__) + std::string("\n[MESSAGE] ") + msg).c_str(), Log::fatal))
#define DEBUG(module, msg) EventManager::GetInstance()->SendEventNow(new Log(module, msg, Log::debug))