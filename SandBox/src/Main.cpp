#include <AppFrame.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <filesystem>

class Application : public Engine::Application {
public:
	Application() {
		//graphic = new Engine::GraphicModule();
		//AddModule(graphic);
		SubscribeToEvent(Engine::Log::Type());//Used for Console module.
	}

	void Run() override;
	bool OnEvent(Engine::BasicEvent & event) override;
	bool Close() {
		return m_Close;
	}

	~Application() {
		//if (graphic) {
	//		delete graphic;
		//}
	}
private:
	bool m_Close;
	//Engine::GraphicModule * graphic;
};

void Application::Run() {
	m_Close = false;
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
	Engine::VFS::GetInstance()->Mount(PhysicalSystem);

	AddModule<Engine::ModuleWindow>(new Engine::ModuleWindow());
	AddModule<Engine::ModuleConsole>(new Engine::ModuleConsole());
	AddModule<Engine::SoundModule>(new Engine::SoundModule());
	AddModule<Engine::ModuleIMGUI>(new Engine::ModuleIMGUI());


	std::cout << "Run" << std::endl;
	Engine::Application::Run();
}
bool Application::OnEvent(Engine::BasicEvent & event) {
	if (Engine::WindowCloses* data = Engine::WindowCloses::Match(&event)) {
		m_Close = true;
		return true;
	}
	if (Engine::WindowResize* data = Engine::WindowResize::Match(&event)) {
		return true;
	}
}


int main() {
	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{
		//Engine::Memory::Scope<Application> app = Engine::Memory::CreateScope<Application>();
		Application * aap = new Application();
		Application::SetInstance(aap);
		AppConfig config;
		aap->SetConfig(&config);
		aap->Run();
		//Examples();

		while (!aap->Close()) {
			aap->OnEarlyUpdate();
			aap->OnUpdate();
			aap->OnLateUpdate();
		}
		aap->Stop();
	}
	std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;

	//ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}