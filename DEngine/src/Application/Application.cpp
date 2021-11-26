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

#include "Core/ResourceManager/ResourceManager.h"
#include "Core/ResourceManager/Resource.h"
#include "Resources/RecourceXML.h"

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


	//taks.Start();
	std::cout << "Fiziniu gijiu skaicius " << std::thread::hardware_concurrency() << std::endl;
	
	RecourceXML* resource = ResourceManager::GetInstace()->GetResource<RecourceXML>("data.xml");
	if (resource && resource->IsAvailable()) {
		std::cout << "data size: " << resource->GetMemoryUsage() << std::endl;
		//resource->Get()->GetDocument();
		tinyxml2::XMLElement* RootElement = resource->Get()->RootElement();
		if (RootElement) {
			tinyxml2::XMLElement* WindowConfig = RootElement->FirstChildElement("Window");
			if (WindowConfig) {
				std::cout << WindowConfig->FirstChildElement("Name")->GetText() << " " << WindowConfig->FirstChildElement("Width")->GetText() << " " <<
					WindowConfig->FirstChildElement("Height")->GetText() << " " << WindowConfig->FirstChildElement("FPS")->GetText() << " ";
			}
			std::cout << RootElement->FirstChildElement("StartupLanguage")->GetText() << " ";

			tinyxml2::XMLElement* SuportedLanguages = RootElement->FirstChildElement("SuportedLanguages");
			if (SuportedLanguages) {
				
				tinyxml2::XMLElement* SuportedLanguage = SuportedLanguages->FirstChildElement("Language");
				while (SuportedLanguage) {
					std::cout << SuportedLanguage->GetText() << " ";
					SuportedLanguage = SuportedLanguage->NextSiblingElement("Language");
				}
			}
		}
	}

	resource = ResourceManager::GetInstace()->GetResource<RecourceXML>("data.xml");

	ResourceManager::GetInstace()->ReleaseResource("data.xml");
	ResourceManager::GetInstace()->ReleaseResource("data.xml");
	ResourceManager::GetInstace()->ReleaseResource("data.xml");


	m_Context = new AppContext(m_Config);
	m_Device = new Device();
	m_Close = false;

	for (Module* module : m_Modules) {
		module->OnInit(m_Context);
	}
	for (Module* module : m_Modules) {
		module->OnStart();
	}
}

void Engine::Application::OnUpdate	() {
	if (taks.CanRetirieve()) {
		std::cout << taks.GetCickles() << std::endl;
	}
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