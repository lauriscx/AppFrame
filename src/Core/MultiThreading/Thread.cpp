#include "Thread.h"

AppFrame::Thread::Thread() {}

void AppFrame::Thread::Start() {
	m_Thread = std::thread(&Thread::Run, this);
}

std::thread::id AppFrame::Thread::GetThreadID() {
	return m_Thread.get_id();
}

unsigned int AppFrame::Thread::GetHardwareConcurrency() {
	return m_Thread.hardware_concurrency();
}

void AppFrame::Thread::Run() {

}

AppFrame::Thread::~Thread() {
	if (m_Thread.joinable()) {
		m_Thread.join();
	}
}
