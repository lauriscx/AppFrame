#pragma once
#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"
#include "Application/AppContext.h"

namespace AppFrame {
	class  ModuleWindow : public Module {
	public:
		ModuleWindow();

		void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		void OnStop() override;

		void* GetWindow() { return m_Window; }

		virtual ~ModuleWindow();

	private:
		void* m_Window;
		static bool Minimized;
	};
}