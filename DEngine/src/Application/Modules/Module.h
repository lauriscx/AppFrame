#pragma once
#include "Core/core.h"
#include "Application/AppContext.h"
#include "Application/Events/AppEvents.h"

namespace Engine {
	class ENGINE_API Module {
	public:
		Module() {};
		virtual void OnInit(AppContext* context) { m_Context = context; };
		virtual void OnStart() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnAppInput(int x, int y, int action, int key) {}
		virtual void OnAppEvent(BasicEvent* event) {}
		virtual void OnStop() {}
		virtual int ID() = 0;
		virtual ~Module() {};
	protected:
		AppContext* m_Context;
	};
}