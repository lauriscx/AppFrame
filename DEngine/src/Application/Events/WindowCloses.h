#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class WindowCloses : public BasicEvent {
	public:
		static int Type() { return Events::WindowCloses; }
		virtual int GetType() override { return Type(); }
	private:

	};
}