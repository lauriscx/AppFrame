#include <DEngine.h>
#include <iostream>


void Examples() {
	struct testData {
		int a;
		const char* b;
		float c;
		const char* d[3];
		//std::string tekstai[3];
	};
	//Posible to create in scope too: Engine::Memory::Scope<Engine::Task<int>> task = Engine::Memory::CreateScope<Engine::Task<int>>();
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

	//if (task->IsAccessible()) {
	//std::cout << "task1 results: " << task->GetResults() << std::endl;
	//}
	//if (task2->IsAccessible()) {
	//	std::cout << "task2 results: " << task2->GetResults() << std::endl;
	//}


	std::filesystem::path path = "/Test/TestDataFile.binary";
	{
		testData data;
		data.a = 115;
		data.b = "Tavo reikalas";
		data.c = 45.99f;
		data.d[0] = "pirmas";
		data.d[1] = "antras";
		data.d[2] = "trecias";


		if (!Engine::FileSystem::WriteBinaryFile(path, (char*)&data, sizeof(testData))) {
			std::cout << "Failed" << std::endl;
		}
	}
	{
		testData NewData;

		if (Engine::FileSystem::ReadBinaryFile(path, (char*)&NewData, sizeof(testData))) {
			std::cout << NewData.a << " " << NewData.b << " " << NewData.c << std::endl;
			std::cout << NewData.d[0] << std::endl;
			std::cout << NewData.d[1] << std::endl;
			std::cout << NewData.d[2] << std::endl;
		}
	}
}

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

std::filesystem::path strip_root(const std::filesystem::path& path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/")
		return std::filesystem::path();
	else
		return strip_root(parent_path) += "/" + path.filename().string();
}

std::filesystem::path get_root(const std::filesystem::path& path) {
	const std::filesystem::path& parent_path = path.parent_path();
	if (parent_path.empty() || parent_path == "/") {
		return path;
	}
	else {
		return get_root(parent_path);
	}
}

int main() {
	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{


		Engine::Memory::Scope<Application> app = Engine::Memory::CreateScope<Application>();
		Application * aap = static_cast<Application*>(Engine::Application::GetInstance());
		aap->GetWindow()->SetTitle("Smakas");
		aap->GetWindow()->SetWidth(800);
		aap->GetWindow()->SetHeight(600);
		app->Run();
		//Examples();

		while (!app->Close()) {
			app->OnUpdate();
		}
	}
	std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;

	ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}