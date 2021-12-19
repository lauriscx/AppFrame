#pragma once
#include "Core/Core.h"

namespace AppFrame {
	class ENGINE_API UUID {
	public:
		UUID();
		~UUID();
	private:
		unsigned __int64 m_UUID;
	};
}