#pragma once
#include "Thread.h"

class TaskManager : public Thread {
public:
	TaskManager();

	virtual void Run() override;

	int GetCickles();
	bool CanRetirieve();

	~TaskManager();
private:
	int m_Cicles;
	bool m_CanRetrieve;
};