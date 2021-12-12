#pragma once
#include "Core/Core.h"
#include "Application/Modules/Module.h"
#include "Application/AppContext.h"

namespace Engine {
	class ENGINE_API ModuleWindow : public Module {
	public:
		ModuleWindow();

		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnStop() override;

		virtual ~ModuleWindow();

	private:
		void* m_Window;
	};
}