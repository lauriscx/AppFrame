#pragma once
#include "Core/Core.h"
#include "Core/EventSystem/Event.h"
#include "Application/Events/EventTypes.h"

namespace AppFrame {
	class InputScroll : public BasicEvent {
	public:
		InputScroll(int x, int y) : X(x), Y(y) {}
		static int Type() { return Events::InputScroll; }
		static InputScroll* Match(BasicEvent* event) {
			if (event->GetType() == Type()) {
				return static_cast<InputScroll*>(event);
			}
			return nullptr;
		}
		virtual int GetType() override { return Type(); }
		int GetX() { return X; }
		int GetY() { return Y; }
	private:
		int X;
		int Y;
	};
}