#include <DEngine.h>
#include <iostream>


class Application : public Engine::Application {
public:
	Application() {
		graphic = new Engine::GraphicModule();
		AddModule(graphic);
	}

	void Run();

	~Application() {
		if (graphic) {
			delete graphic;
		}
	}
private:
	Engine::GraphicModule * graphic;
};

void Application::Run() {
	std::cout << "Run" << std::endl;
	Engine::Application::Run();
}

int main() {

	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{

		/* Example off automatic memory managment */
		Engine::Memory::Scope<Application> app = Engine::Memory::CreateScope<Application>();
		Application * aap = static_cast<Application*>(Engine::Application::GetInstance());
		aap->GetWindow()->SetTitle("Smakas");
		aap->GetWindow()->SetWidth(800);
		aap->GetWindow()->SetHeight(600);
		//Engine::Application* app = new Engine::Application();
		app->Run();


		Engine::Memory::Reference<Engine::Task<int>> task = Engine::Memory::CreateReference<Engine::Task<int>>();
		Engine::Memory::Reference<Engine::Task<int>> task2 = Engine::Memory::CreateReference<Engine::Task<int>>();;

		task = Engine::Memory::CreateReference<Engine::Task<int>>();
		task->CreateAsyncTask([](int a) {
			int sum = 0;
			for (size_t i = 0; i < 100; i++)
			{
				sum += a;
			}
			return sum;
		}, 1);

		task2 = Engine::Memory::CreateReference<Engine::Task<int>>();
		task2->CreateAsyncTask([](int a)->int {
			int sum = 0;
			for (size_t i = 0; i < 100; i++)
			{
				sum += a;
			}
			return sum;
		}, 2);

		while (!app->Close()) {
			app->OnUpdate();

			if (task->IsAccessible()) {
				std::cout << "task1 results: " << task->GetResults() << std::endl;
			}
			if (task2->IsAccessible()) {
				std::cout << "task2 results: " << task2->GetResults() << std::endl;
			}
		}
		//delete  app;
	}
	std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;

	ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}