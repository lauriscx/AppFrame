#pragma once
#include "Core/Core.h"
#include "Core/Hardware/Device.h"
#include "Application/Modules/Module.h"
#include "Core/EventSystem/EventHandler.h"
#include "Core/InputSystem/InputHandler.h"
#include "AppContext.h"
#include "AppConfig.h"
#include "Application/Modules/Windows/ModuleWindow.h"
#include "Core/Utils/Timer.h"

#include <vector>

#include "Core/MultiThreading/TaskManager.h"

namespace Engine {
	class ENGINE_API Application : public EventHandler, public InputHandler {
	public:
		enum Status {
			Unknow = 1 << 0,
			Closed = 1 << 1,
			Closing = 1 << 2,
			Paused = 1 << 3,
			Pausing = 1 << 4,
			Started = 1 << 5,
			Starting = 1 << 6,
			Running = 1 << 7,
			Loading = 1 << 8
		};
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

		virtual void AddStatus(Status status);
		virtual void RemoveStatus(Status status);
		virtual bool IsStatus(Status status);
		virtual Status GetStatus();

		virtual ~Application();
	/* Application data */
	private:
		AppConfig * m_Config;
		AppContext* m_Context;
		Device	  * m_Device;
		TaskManager taks;

		Status m_Status;
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