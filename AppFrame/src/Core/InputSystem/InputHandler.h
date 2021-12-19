#pragma once
#include "Core/Core.h"

namespace Engine {
	class ENGINE_API InputHandler {
	public:
		InputHandler();

		/* If return true it means that event was consumed and other objects do not get it. */
		virtual bool OnInput(int x, int y, int action, int key) { return false; }

		virtual ~InputHandler();
	};
}