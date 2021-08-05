#pragma once
#include <map>
#include <vector>
#include <mutex>

namespace Engine {
	class EventHandler;
	class BasicEvent;

	class EventManager {
	protected://Using this functions only EventHandler class.
		void Surscribe(int eventType, EventHandler* eventHandler);
		void UnSurscribe(int eventType, EventHandler* eventHandler);
		void UnSurscribe(EventHandler* eventHandler);

	public:
		void SendEvent(BasicEvent* event);
		void SendEventNow(BasicEvent* event);

		void Update();

		static EventManager* GetInstance();

	private:
		~EventManager() { m_EventHandlerEvents.clear(); }
		EventManager() {}
		EventManager(const EventManager& eventManager) {}
		EventManager(const EventManager&& eventManager) {}
		EventManager& operator=(const EventManager& eventmanager) {}

		std::multimap<int, EventHandler*> m_EventHandlerEvents;
		std::vector<BasicEvent*> m_Events;

		std::mutex m_Mutex;

		friend EventHandler;
	};
}