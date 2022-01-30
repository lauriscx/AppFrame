#pragma once
#include "Core/Core.h"

namespace AppFrame {
	class InputHandler {
	public:
		InputHandler();

		/* If return true it means that event was consumed and other objects do not get it. */
		virtual bool OnInput(int x, int y, int action, int key) = 0;

		virtual ~InputHandler();
	};
}