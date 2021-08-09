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
	struct testData {
		int a;
		std::string b;
		float c;
		std::string tekstai[3];
	};


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


		Engine::FileSystem::CreateDirectory("/Test");

		if (Engine::FileSystem::CreateFile("/Test/TestDataFile.binary")) {
			std::cout << "created" << std::endl;
		}
		else {
			std::cout << "Failed create" << std::endl;
		}

		{
			testData data;
			data.a = 115;
			data.b = "Tavo reikalas";
			data.c = 45.99f;
			data.tekstai[0] = ("pirmas");
			data.tekstai[1] = ("antras");
			data.tekstai[2] = ("trecias");

			if (Engine::FileSystem::WriteBinaryFile("/Test/TestDataFile.binary", (char*)&data, sizeof(testData))) {
				std::cout << "writed" << std::endl;
			}
			else {
				std::cout << "Failed write" << std::endl;
			}
		}


		if (Engine::FileSystem::IsFileExists("/Test/TestDataFile.binary")) {
			Engine::int64 size;
			Engine::FileSystem::FileSize("/Test/TestDataFile.binary", &size);
			std::cout << size << std::endl;
		}

		testData NewData;

		if (Engine::FileSystem::ReadBinaryFile("/Test/TestDataFile.binary", (char*)&NewData, sizeof(testData))) {
			std::cout << "successfull read" << std::endl;
			std::cout << NewData.a << " " << NewData.b.c_str() << " " << NewData.c << std::endl;

			std::cout << NewData.tekstai[0].c_str() << std::endl;
			std::cout << NewData.tekstai[1].c_str() << std::endl;
			std::cout << NewData.tekstai[2].c_str() << std::endl;
			/*for (auto a : NewData.tekstai) {
				std::cout << a.c_str() << std::endl;
			}*/
		}
		else {
			std::cout << "Failed read" << std::endl;
		}


		while (!app->Close()) {
			app->OnUpdate();

			/*if (task->IsAccessible()) {
				std::cout << "task1 results: " << task->GetResults() << std::endl;
			}
			if (task2->IsAccessible()) {
				std::cout << "task2 results: " << task2->GetResults() << std::endl;
			}*/
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