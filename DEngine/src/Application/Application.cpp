//#include "DEnginePch.h"
#include "Application.h"
#include "Application/Events/AppEvents.h"
#include "Asserts.h"
#include <iostream>
#include "Platform/Windows/WinWindow.h"
#include <filesystem>
#include "Core/FileSystem/FileSystem.h"
#include "Core/VirtualFileSystem/VFS.h"

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application() : EventHandler("Application") {
	ASSERT((s_Instance == nullptr));
	s_Instance = this;
	m_Config	= new AppConfig();
	m_Context	= new AppContext(m_Config);
	m_Window	= new WinWindow();
	close = false;
	SubscribeToEvent(0);
	SubscribeToEvent(1);
}

void Engine::Application::Run() {
	{
		std::filesystem::path path = "/res/kaskas/bitai/failas.bin";

		if (Engine::VFS::GetInstance().Mount("/res", "/RES")) {
			std::cout << "Mounted" << std::endl;
		}
		if (Engine::VFS::GetInstance().Mount("/res", "/resources")) {
			std::cout << "Mounted" << std::endl;
		}

		//std::cout << "Realus adresas: " << path.string().c_str() << std::endl;
		//path.remove_filename();
		//std::cout << "Be failo adresas: " << path.string().c_str() << std::endl;
		//std::cout << "just path: " << std::filesystem::path().string().c_str() << std::endl;
		//std::filesystem::strip_root(path);
		//std::filesystem::path::iterator it = path.begin();
		//it++;
		//std::cout << "parent path: " << path.parent_path().string().c_str() << std::endl;
		std::cout << "phycal file path: " << Engine::VFS::GetInstance().GetPath(path) << std::endl;

	}
	m_Window->Create(m_Context);

}

void Engine::Application::OnUpdate() {
	for (Module* module : m_Modules) {
		module->Update(0.0f);
	}
	m_Window->OnUpdate();
}

bool Engine::Application::OnEvent(BasicEvent & event) {
	if (event.GetType() == Events::WindowCloses) {
		close = true;
		//std::cout << "Should application exit" << std::endl;
		return true;
	}
	if (event.GetType() == WindowResize::Type()) {
		WindowResize * windoResize = static_cast<WindowResize*>(&event);
		//std::cout << "Window size changed : x(" << windoResize->GetX() << "), y(" << windoResize->GetY() << ")" << std::endl;
		return true;
	}
	return false;
}

bool Engine::Application::OnInput(int x, int y, int action, int key) {
	//std::cout << "Action: " << action << " key: " << key << " x: " << x << " y: " << y << std::endl;
	return true;
}

bool Engine::Application::Close() {
	return close;
}

void Engine::Application::AddModule(Module * module) {
	m_Modules.push_back(module);
}

AppConfig * Engine::Application::GetConfig() {
	return m_Config;
}

AppContext * Engine::Application::GetContext() {
	return m_Context;
}

Engine::AppWindow * Engine::Application::GetWindow()
{
	return m_Window;
}

Engine::Device * Engine::Application::GetDevice()
{
	return m_Device;
}

Engine::Application::~Application() {

	delete m_Window;
}
