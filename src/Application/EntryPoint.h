#pragma once

#include "AppFrame.h"

extern 

int main(int argc, char** argv) {
	//std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{
		AppFrame::PhysicalMountPoint * PhysicalSystem = new AppFrame::PhysicalMountPoint();
		PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Application");
		AppFrame::VFS::GetInstance()->Mount(PhysicalSystem);

		//aap->SetConfig(&config);
		aap->Run();
		while (!aap->Close()) {
			aap->OnEarlyUpdate();
			aap->OnUpdate();
			aap->OnLateUpdate();
		}
		aap->Stop();
		delete aap;
	}
	/*{
		using namespace AppFrame;
		INFO("ArcticFox", (std::string("Left with memory : ")			+ std::to_string(m_MemoryAllocated - m_MemoryRelease)).c_str());
		INFO("ArcticFox", (std::string("Left with memory current : ")	+ std::to_string(m_MemoryCurrentMemory)).c_str());
		INFO("ArcticFox", (std::string("Allocated memory  : ")			+ std::to_string(m_MemoryAllocated)).c_str());
		INFO("ArcticFox", (std::string("Rleased memory : ")				+ std::to_string(m_MemoryRelease)).c_str());
	}*/
	/*std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;*/

	//ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}