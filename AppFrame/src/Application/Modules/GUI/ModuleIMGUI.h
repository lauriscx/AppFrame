#pragma once
#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

namespace AppFrame {
	class ENGINE_API ModuleIMGUI : public Module {
	public:
		ModuleIMGUI();

		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		virtual void OnAppInput(int x, int y, int action, int key) override;
		virtual void OnAppEvent(BasicEvent* event) override;
		virtual void OnStop() override;

		virtual ~ModuleIMGUI();
	};
}