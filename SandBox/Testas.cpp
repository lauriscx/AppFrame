/*#include <DEngine.h>
#include <iostream>
#include <Core/EventSystem/Event.h>
#include <Core/EventSystem/EventManager.h>

class Moved : public Engine::BasicEvent {
public:
	Moved() {}
	virtual ~Moved() {}
	virtual int			GetType() { return 1; }
	virtual const char* toString() { return "Pajudejo"; }
	float XPosition() { return 50.5f; }
	float YPosition() { return 25.5f; }
};

class Clicked : public Engine::BasicEvent {
public:
	Clicked(float key) { this->key = key; }
	virtual int			GetType() { return 2; }
	virtual const char* toString() { return "Paspausta"; }
	int Key() { return key; }
	virtual ~Clicked() {}
private:
	int key;
};


class Player : public Engine::EventHandler {
public:
	virtual bool OnEvent(Engine::BasicEvent& event) override {
		if (event.GetType() == 1) {
			Moved* ev = static_cast<Moved*>(&event);
			std::cout << "Player " << event.toString() << "X: " << ev->XPosition() << " Y:" << ev->YPosition() << std::endl;
		}
		return false;
	}
	Player() {
		SubscribeToEvent(1);
	}
	~Player() {}


};
class NPC : public Engine::EventHandler {
public:
	virtual bool OnEvent(Engine::BasicEvent& event) override {
		if (event.GetType() == 2) {
			Clicked* ev = static_cast<Clicked*>(&event);
			std::cout << "NPC " << event.toString() << "Key: " << ev->Key() << std::endl;
		}

		return false;
	}
	NPC() {
		SubscribeToEvent(2);
	}
	~NPC() {}
};

int main() {
	Player* player = new Player();
	NPC* npc = new NPC();
	Moved* moved = new Moved();
	Engine::EventManager::GetInstance()->SendEvent(moved);
	Engine::EventManager::GetInstance()->SendEvent(new Clicked(60.0f));
	Engine::EventManager::GetInstance()->Update();

	while (true) {

	}
	return 0;
}*/