#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class WindowMinimized : public BasicEvent {
	public:
		WindowMinimized() {}
		static int Type() { return Events::WindowMinimized; }
		static WindowMinimized* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<WindowMinimized*>(event);
			}
			return nullptr;
		}
		virtual int GetType() override { return Type(); }
	};
}