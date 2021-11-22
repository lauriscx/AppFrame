#include "Application.h"
#include "Asserts.h"
#include "Application/Events/AppEvents.h"
#include <iostream>
#include <filesystem>

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <filesystem>
#include "Core/XML/XML.h"

#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/VFS/MountPoints/PhysicalMountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/ARFMountPoint.h"
#include "Core/FileSystem/File.h"



Engine::Application::Application() : EventHandler("Application") {
	/* Important init data only in run function */

	/* Here subscribe crucial events for application */
	SubscribeToEvent(WindowCloses::Type());
	SubscribeToEvent(WindowResize::Type());
}

void Engine::Application::AddModule(Module * module) {
	m_Modules.push_back(module);
}

void Engine::Application::Run() {

	ARFMountPoint * VirtualFiles = new ARFMountPoint();
	//VirtualFiles->CreateMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VirtualFiles->SetMountPoint("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VFS::GetInstance().Mount(VirtualFiles);

	PhysicalMountPoint * PhysicalSystem = new PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Export");

	File* file = PhysicalSystem->ReadFile("zip.zip");

	VirtualFiles->WriteFile("VirtualFileSystem/zip.zip", file->GetData(), file->GetSize());
	//VirtualFiles->RemoveFile("VirtualFileSystem/zip.zip");




	/*PhysicalMountPoint * PhysicalSystem = new PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Export");
	VFS::GetInstance().Mount(PhysicalSystem);

	PhysicalMountPoint * _PhysicalSystem = new PhysicalMountPoint();
	_PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Import");
	VFS::GetInstance().Mount(_PhysicalSystem);


	char* data = VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/Export")->ReadFile("zip.zip", 0);
	int size = VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/Export")->FileSize("zip.zip");

	VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF")->WriteFile("C:/Users/Kosmosas/Desktop/Import/zip.zip", data, size);

	char* _data = VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF")->ReadFile("C:/Users/Kosmosas/Desktop/Import/zip.zip", 0);
	int _size = VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF")->FileSize("C:/Users/Kosmosas/Desktop/Import/zip.zip");

	VFS::GetInstance().GetMount("C:/Users/Kosmosas/Desktop/Import")->WriteFile("zip.zip", _data, _size);*/


	m_Context = new AppContext(m_Config);
	m_Close = false;

	for (Module* module : m_Modules) {
		module->OnInit(m_Context);
	}
	for (Module* module : m_Modules) {
		module->OnStart();
	}
}

void Engine::Application::OnUpdate	() {
	m_Timer.Start();
	for (Module* module : m_Modules) {
		module->OnUpdate(m_Timer.Elapsed());
	}
	m_Timer.Stop();
}
bool Engine::Application::OnEvent	(BasicEvent & event) {
	for (Module* module : m_Modules) {
		module->OnAppEvent(&event);
	}
	if (WindowCloses* data = WindowCloses::Match(&event)) {
		m_Close = true;
		//std::cout << "Should application exit" << std::endl;
		return true;
	}
	if (WindowResize* data = WindowResize::Match(&event)) {
		std::cout << "Window size changed : x(" << data->GetX() << "), y(" << data->GetY() << ")" << std::endl;
		return true;
	}
	return false;
}
bool Engine::Application::OnInput	(int x, int y, int action, int key) {
	for (Module* module : m_Modules) {
		module->OnAppInput(x, y, action, key);
	}
	//std::cout << "Action: " << action << " key: " << key << " x: " << x << " y: " << y << std::endl;
	return true;
}

AppConfig		* Engine::Application::GetConfig	() {
	return m_Config;
}
AppContext		* Engine::Application::GetContext	() {
	return m_Context;
}
Engine::Device	* Engine::Application::GetDevice	() {
	return m_Device;
}

bool Engine::Application::Close	() {
	return m_Close;
}
void Engine::Application::Stop	() {
	for (Module* module : m_Modules) {
		module->OnStop();
	}
	delete m_Context;
}

Engine::Application::~Application() {}