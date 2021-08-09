//#include "DEnginePch.h"
#include "Application.h"
#include "Application/Events/AppEvents.h"
#include "Asserts.h"
#include <iostream>
#include "Platform/Windows/WinWindow.h"

#include "Core/FileSystem/FileSystem.h"

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application() : EventHandler("Application") {
	ASSERT((s_Instance == nullptr));
	s_Instance = this;
	m_Window = new WinWindow();
	close = false;
	SubscribeToEvent(0);
	SubscribeToEvent(1);
}

void Engine::Application::Run() {
	m_Window->Create();

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

Engine::Window * Engine::Application::GetWindow()
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
