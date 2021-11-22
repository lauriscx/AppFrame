#pragma once
#include "Core/core.h"
#include "Application/Modules/Module.h"

namespace Engine {
	class ENGINE_API GraphicModule : public Module {
	public:
		GraphicModule() {}

		virtual void OnUpdate(float deltaTime) override;

		virtual ~GraphicModule() {}
	};
}
