#pragma once
#include "Core/Core.h"
#include "Thread.h"

class ENGINE_API TaskManager : public Thread {
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