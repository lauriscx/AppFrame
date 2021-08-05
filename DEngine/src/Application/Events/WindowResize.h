#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace Engine {
	class WindowResize : public BasicEvent {
	public:
		WindowResize(int x, int y) : X(x), Y(y) {}
		static int Type() { return Events::WindowResize; }
		virtual int GetType() override { return Type(); }
		int GetX() { return X; }
		int GetY() { return Y; }
	private:
		int X;
		int Y;
	};
}