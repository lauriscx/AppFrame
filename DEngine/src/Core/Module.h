#pragma once

namespace Engine {
	class Module {
	public:
		Module() {};
		virtual void Update(float deltaTime) = 0;
		virtual ~Module() {};
	};
}