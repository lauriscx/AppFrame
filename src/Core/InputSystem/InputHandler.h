#pragma once
#include "Core/Core.h"

namespace AppFrame {
	class InputData;
	class InputHandler {
	public:
		InputHandler();

		/* If return true it means that event was consumed and other objects do not get it. */
		virtual bool OnInput(const InputData& input) = 0;

		virtual ~InputHandler();
	};
}