#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class WindowMaximized : public BasicEvent {
	public:
		WindowMaximized(const char* language) {}
		static int Type() { return Events::WindowMaximized; }
		virtual int GetType() override { return Type(); }
	};
}