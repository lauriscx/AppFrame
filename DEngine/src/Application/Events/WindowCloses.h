#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class WindowCloses : public BasicEvent {
	public:
		static int Type() { return Events::WindowCloses; }
		static WindowCloses* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<WindowCloses*>(event);
			}
			return nullptr;
		}
		virtual int GetType() override { return Type(); }
	private:

	};
}