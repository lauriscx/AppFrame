#include <DEngine.h>
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
	}

	void Run();

	~Application() {
		//if (graphic) {
	//		delete graphic;
		//}
	}
private:
	//Engine::GraphicModule * graphic;
};

void Application::Run() {
	std::cout << "Run" << std::endl;
	Engine::Application::Run();
}


int main() {
	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{
		//Engine::Memory::Scope<Application> app = Engine::Memory::CreateScope<Application>();
		Application * aap = static_cast<Application*>(Engine::Application::GetInstance());
		AppConfig config;
		aap->SetConfig(&config);
		Engine::ModuleWindow window;
		aap->AddModule(&window);
		aap->Run();
		//Examples();

		while (!aap->Close()) {
			aap->OnUpdate();
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