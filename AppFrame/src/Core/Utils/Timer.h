#pragma once
#include <chrono>
#include "Core/Core.h"

namespace AppFrame {
	class  Timer {
	public:
		Timer() : m_Elapsed(0) {}
		void Start() {
			m_Start = std::chrono::high_resolution_clock::now();
		}
		void Stop() {
			m_End = std::chrono::high_resolution_clock::now();
			m_Elapsed = elapsed();
		}
		float Elapsed() {
			return m_Elapsed;
		}
		~Timer() {}

	private:
		float elapsed() {
			return std::chrono::duration<float, std::milli>(m_End - m_Start).count();
		}

		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		std::chrono::time_point<std::chrono::steady_clock> m_End;
		float m_Elapsed;
	};
}