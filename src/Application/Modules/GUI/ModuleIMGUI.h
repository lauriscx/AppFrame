#pragma once
#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"
//#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImGuizmo.h"
#include "glm/glm.hpp"

namespace AppFrame {
	class InputData;
	class ModuleIMGUI : public Module {
	public:
		ModuleIMGUI();

		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		virtual void OnAppInput(const InputData& input) override;
		virtual void OnAppEvent(BasicEvent* event) override;
		virtual void OnStop() override;

		virtual ~ModuleIMGUI();
	};
}

namespace ImGui {
	bool ModifiedDecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
}