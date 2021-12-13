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
#include "Core/EventSystem/EventManager.h"

#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/VFS/MountPoints/PhysicalMountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/ARFMountPoint.h"
#include "Core/FileSystem/File.h"

#include "Core/ResourceManager/ResourceManager.h"
#include "Core/ResourceManager/Resource.h"
#include "Resources/RecourceXML.h"

#include "Modules/Sound/SoundModule.h"
#include "Modules/Console/ModuleConsole.h"
#include "Modules/GUI/ModuleGUI.h"
#include "Modules/Windows/ModuleWindow.h"

#include "Logger.h"

Engine::Application::Application() : EventHandler("Application") {
	/* Important init data only in run function */

	/* Here subscribe crucial events for application */
	SubscribeToEvent(WindowCloses::Type());
	SubscribeToEvent(WindowResize::Type());
	SubscribeToEvent(Log::Type());//Used for Console module.
}

void Engine::Application::Run() {

	/*ARFMountPoint * VirtualFiles = new ARFMountPoint();
	//VirtualFiles->CreateMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VirtualFiles->SetMountPoint("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VFS::GetInstance().Mount(VirtualFiles);

	PhysicalMountPoint * PhysicalSystem = new PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Export/");
	VFS::GetInstance().Mount(PhysicalSystem);

	PhysicalMountPoint * _PhysicalSystem = new PhysicalMountPoint();
	_PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Import/");
	VFS::GetInstance().Mount(_PhysicalSystem);



	File* file = PhysicalSystem->ReadFile("Data/zip.zip");//Get file from exports folder.
	VirtualFiles->WriteFile(file);//write file to virtual file system.
	File* VRfile = VirtualFiles->ReadFile("Data/zip.zip");
	ASSERT(VRfile != nullptr);
	_PhysicalSystem->WriteFile(VRfile);//write file to virtual file system.*/

	PhysicalMountPoint * PhysicalSystem = new PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Application/");
	VFS::GetInstance()->Mount(PhysicalSystem);


	m_Context = new AppContext(m_Config);
	m_Device = new Device(); 
	m_Close = false;
	//AddModule(new SoundModule());
	AddModule<ModuleWindow>(new ModuleWindow());
	AddModule<ModuleConsole>(new ModuleConsole());
	AddModule<ModuleGUI>(new ModuleGUI());

	for (auto module : m_Modules) {
		module.second->OnInit(m_Context);
	}
	for (auto module : m_Modules) {
		module.second->OnStart();
	}
}

void Engine::Application::OnEarlyUpdate() {
	m_Timer.Start();
	for (auto module : m_Modules) {
		module.second->OnEarlyUpdate(m_Timer.Elapsed());
	}
}

void Engine::Application::OnUpdate	() {
	for (auto module : m_Modules) {
		module.second->OnUpdate(m_Timer.Elapsed());
	}
}

void Engine::Application::OnLateUpdate() {
	for (auto module : m_Modules) {
		module.second->OnLateUpdate(m_Timer.Elapsed());
	}
	m_Timer.Stop();
}

bool Engine::Application::OnEvent	(BasicEvent & event) {
	for (auto module : m_Modules) {
		module.second->OnAppEvent(&event);
	}
	if (WindowCloses* data = WindowCloses::Match(&event)) {
		m_Close = true;
		return true;
	}
	if (WindowResize* data = WindowResize::Match(&event)) {
		return true;
	}
	return false;
}
bool Engine::Application::OnInput	(int x, int y, int action, int key) {
	for (auto module : m_Modules) {
		module.second->OnAppInput(x, y, action, key);
	}
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
	for (auto module : m_Modules) {
		module.second->OnStop();
	}
	delete m_Context;
}

void Engine::Application::AddStatus(Status status) {
	m_Status = (Status)(m_Status | status);
}
void Engine::Application::RemoveStatus(Status status) {
	m_Status = (Status)(m_Status & ~status);
}
bool Engine::Application::IsStatus(Status status) {
	return m_Status & status;
}
Engine::Application::Status Engine::Application::GetStatus() {
	return m_Status;
}

Engine::Application::~Application() {}