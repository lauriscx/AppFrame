#pragma once
#include "Core/Core.h"
#include "Application/AppContext.h"

namespace Engine {
	class ENGINE_API AppWindow {
	public:
		AppWindow() {}
		virtual bool Create(AppContext* context) = 0;

		virtual void SetTitle(const char* title) = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual void SetVSync(bool vsync) = 0;

		virtual const char* GetTitle() = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual bool GetVSync() const = 0;

		virtual void OnUpdate() = 0;
		virtual bool Closed() = 0;

		virtual ~AppWindow() {}
	};
}