#pragma once
#include "Core/core.h"
#include "Core/Module.h"

namespace Engine {
	class ENGINE_API GraphicModule : public Module {
	public:
		GraphicModule() {}

		virtual void Update(float deltaTime) override;

		virtual ~GraphicModule() {}
	};
}
