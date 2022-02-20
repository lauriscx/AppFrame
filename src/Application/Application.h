#pragma once
#include "Core/Core.h"
#include "AppContext.h"
#include "AppConfig.h"
#include "Core/EventSystem/EventHandler.h"
#include "Core/InputSystem/InputHandler.h"
#include "Core/ModuleSystem/Module.h"
#include "Core/ModuleSystem/ModuleRegistry.h"
#include "Core/Hardware/Device.h"
#include "Core/Utils/Timer.h"
#include <filesystem>
#include "Core/FileSystem/VFS/VFS.h"

namespace AppFrame {
	class Application : public EventHandler, public InputHandler, public ModuleRegistry, public AppContext {
	public:
		Application(AppFrame::AppConfig* config);

		inline void SetConfig(AppConfig* config) { m_Config = config; }

		virtual void Run();

		virtual void OnEarlyUpdate();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual bool OnEvent(BasicEvent& event) override;
		virtual bool OnInput(const InputData& input) override;

		template<typename T>
		static T* Module() { return s_Instance->GetModule<T>(); }

		static Application* GetInstance() { return s_Instance; }
		static void SetInstance(Application* instance) { s_Instance = instance; }

		virtual AppConfig	* GetConfig();
		virtual Device		* GetDevice();

		virtual void Stop();

		virtual ~Application();
	/* Application data */
	private:
		AppConfig * m_Config;
		Device	  * m_Device;

		Timer m_Timer;
		 
		static Application* s_Instance;
	};
}