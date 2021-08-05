#pragma once
#include "Core/core.h"

namespace Engine {
	class ENGINE_API Module {
	public:
		Module() {};
		virtual void Update(float deltaTime) = 0;
		virtual ~Module() {};
	};
}