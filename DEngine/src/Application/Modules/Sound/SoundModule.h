#pragma once
#include "Application/Modules/Module.h"

namespace Engine {
	class SoundModule : public Module {
	public:
		SoundModule();
		virtual ~SoundModule();

		virtual int ID() override;
	private:
	};
}