#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace AppFrame {
	class WindowMaximized : public BasicEvent {
	public:
		WindowMaximized(const char* language) {}
		static int Type() { return Events::WindowMaximized; }
		static WindowMaximized* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<WindowMaximized*>(event);
			}
			return nullptr;
		}
		virtual int GetType() override { return Type(); }
	};
}