#pragma once
#include "Core/Core.h"
#include "Core/Hardware/Device.h"
#include "Application/Modules/Module.h"
#include "Core/EventSystem/EventHandler.h"
#include "Core/InputSystem/InputHandler.h"
#include "AppContext.h"
#include "AppConfig.h"
#include "Application/Modules/ModuleWindow.h"
#include "Core/Utils/Timer.h"

#include <vector>

namespace Engine {
	class ENGINE_API Application : public EventHandler, public InputHandler {
	public:
		Application();

		inline void SetConfig(AppConfig* config) { m_Config = config; }
		void AddModule(Module* module);//change to use memory ref.

		virtual void Run();

		virtual void OnUpdate();
		virtual bool OnEvent(BasicEvent& event) override;
		virtual bool OnInput(int x, int y, int action, int key) override;

		static Application* GetInstance() { static Application s_Instance; return &s_Instance; }
		template <typename T>
		T* GetModule(int ID);
		virtual AppConfig	* GetConfig();
		virtual AppContext	* GetContext();
		virtual Device		* GetDevice();

		virtual bool Close();
		virtual void Stop();

		virtual ~Application();
	/* Application data */
	private:
		AppConfig * m_Config;
		AppContext* m_Context;
		Device	  * m_Device;

		Timer m_Timer;

		bool m_Close;

		std::vector<Module*> m_Modules;
	};

	template<typename T>
	inline T* Application::GetModule(int ID) {
		for (Module* module : m_Modules) {
			if (module->ID() == ID) {
				return static_cast<T*>(module);
			}
		}
		return nullptr;
	}
}