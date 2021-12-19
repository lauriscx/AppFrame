#pragma once
#include "Core/core.h"
#include "Application/AppContext.h"
#include "Application/Events/AppEvents.h"

#include <functional>

namespace Engine {
	class ENGINE_API Module {
	public:
		Module() {};
		virtual void OnInit(AppContext* context) { m_Context = context; };
		virtual void OnStart() {}
		virtual void OnEarlyUpdate(float deltaTime) {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnLateUpdate(float deltaTime) {}
		virtual void OnAppInput(int x, int y, int action, int key) {}
		virtual void OnAppEvent(BasicEvent* event) {}
		virtual void OnStop() {}

		std::function<void(const char*, const char*, unsigned int, const char*)> Fatal;
		std::function<void(const char*, const char*, unsigned int, const char*)> Error;
		std::function<void(const char*, const char*, unsigned int, const char*)> Warning;
		std::function<void(const char*, const char*, unsigned int, const char*)> Info;
		std::function<void(const char*, const char*, unsigned int, const char*)> Trace;
		std::function<void(const char*, const char*, unsigned int, const char*)> Debug;
		
		virtual ~Module() {};
	protected:
		AppContext* m_Context;

	};
}