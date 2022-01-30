#include "TaskManager.h"
#include <iostream>

AppFrame::TaskManager::TaskManager() {
	m_CanRetrieve = false;
}

void AppFrame::TaskManager::Run() {
	uint32_t value = 0;
	while (true) {
		value++;
		if (value > 900000000) {
			std::cout << "Working on paralel thread" << std::endl;
			value = 0;
			m_Cicles++;
			m_CanRetrieve = true;
		}
	}
}

int AppFrame::TaskManager::GetCickles() {
	m_CanRetrieve = false;
	return m_Cicles;
}

bool AppFrame::TaskManager::CanRetirieve() {
	return m_CanRetrieve;
}

AppFrame::TaskManager::~TaskManager() {}