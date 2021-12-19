#include "Thread.h"

Thread::Thread() {}

void Thread::Start() {
	m_Thread = std::thread(&Thread::Run, this);
}

std::thread::id Thread::GetThreadID() {
	return m_Thread.get_id();
}

unsigned int Thread::GetHardwareConcurrency() {
	return m_Thread.hardware_concurrency();
}

void Thread::Run() {

}

Thread::~Thread() {
	if (m_Thread.joinable()) {
		m_Thread.join();
	}
}
