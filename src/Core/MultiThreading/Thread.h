#pragma once
#include "Core/Core.h"
#include <thread>
#include <mutex>

namespace AppFrame {
	class Thread {
	public:
		Thread();

		void Start();

		std::thread::id GetThreadID();
		unsigned int GetHardwareConcurrency();
		virtual void Run();

		~Thread();

	private:
		std::thread m_Thread;
		std::mutex m_Mutex;
	};
}