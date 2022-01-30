#pragma once

#include "Core/Core.h"
#include "Core/EventSystem/EventHandler.h"
#include "Core/InputSystem/InputHandler.h"
#include "Core/ModuleSystem/Module.h"
#include "Core/ModuleSystem/ModuleRegistry.h"
#include "Core/Hardware/Device.h"
#include "Core/Utils/Timer.h"

#include "Application/AppContext.h"
#include "Application/AppConfig.h"

namespace AppFrame {
	class  Application : public EventHandler, public InputHandler, public ModuleRegistry, public AppContext {
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
		Application(AppFrame::AppConfig* config);

		inline void SetConfig(AppConfig* config) { m_Config = config; }

		virtual void Run();

		virtual void OnEarlyUpdate();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual bool OnEvent(BasicEvent& event) override;
		virtual bool OnInput(int x, int y, int action, int key) override;

		static Application* GetInstance() { return s_Instance; }
		static void SetInstance(Application* instance) { s_Instance = instance; }

		virtual AppConfig	* GetConfig();
		virtual Device		* GetDevice();

		virtual void Stop();

		virtual void AddStatus(Status status);
		virtual void RemoveStatus(Status status);
		virtual bool IsStatus(Status status);
		virtual Status GetStatus();

		virtual ~Application();
	/* Application data */
	private:
		AppConfig * m_Config;
		Device	  * m_Device;

		Status m_Status;
		Timer m_Timer;

		virtual void OnFatal	(const char* module, const char* file, unsigned int line, const char* msg);
		virtual void OnError	(const char* module, const char* file, unsigned int line, const char* msg);
		virtual void OnWarning	(const char* module, const char* file, unsigned int line, const char* msg);
		virtual void OnInfo		(const char* module, const char* file, unsigned int line, const char* msg);
		virtual void OnTrace	(const char* module, const char* file, unsigned int line, const char* msg);
		virtual void OnDebug	(const char* module, const char* file, unsigned int line, const char* msg);

		static Application* s_Instance;
	};
}