#pragma once
#include "Application/Modules/Module.h"

namespace Engine {
	class ModuleConsole : public Module {
	public:
		ModuleConsole();
		virtual ~ModuleConsole();

		virtual void OnAppInput(int x, int y, int action, int key) override;

		virtual int ID() override;     
	private:
	};
}