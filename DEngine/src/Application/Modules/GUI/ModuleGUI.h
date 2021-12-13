#pragma once
#include "Application/Modules/Module.h"
#include "Core/Core.h"

namespace Engine {
	class ModuleGUI : public Module {
	public:
		ModuleGUI();

		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		virtual void OnAppInput(int x, int y, int action, int key) override;
		virtual void OnAppEvent(BasicEvent* event) override;
		virtual void OnStop() override;

		virtual ~ModuleGUI();
	};
}