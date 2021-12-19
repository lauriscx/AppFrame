#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager() {
	m_CanRetrieve = false;
}

void TaskManager::Run() {
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

int TaskManager::GetCickles() {
	m_CanRetrieve = false;
	return m_Cicles;
}

bool TaskManager::CanRetirieve() {
	return m_CanRetrieve;
}

TaskManager::~TaskManager() {}