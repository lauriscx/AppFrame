//#include "DEnginePch.h"
#include "EventHandler.h"
#include "EventManager.h"

Engine::EventManager * Engine::EventManager::GetInstance() {
	static EventManager instance; return &instance;
}

void Engine::EventManager::Surscribe	(int eventType, EventHandler * eventHandler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_EventHandlerEvents.insert(std::make_pair(eventType, eventHandler));
}
void Engine::EventManager::UnSurscribe	(int eventType, EventHandler * eventHandler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	/* Store 2 pointers from map. First pointer stores address where stars objects with key value,
	 * second stores addres where ends objects with key value.
	 */
	std::pair<std::multimap<int, EventHandler*>::iterator, std::multimap<int, EventHandler*>::iterator> range;
	/*
	 * Get by object range in map.
	 */
	range = m_EventHandlerEvents.equal_range(eventType);
	/*
	 * Iterate through map in specific range.
	 */
	for (std::multimap<int, EventHandler*>::iterator it = range.first; it != range.second; it++) {
		//Send subscripted event to event handler.
		if (it->second == eventHandler) {
			//Remove subscription.
			m_EventHandlerEvents.erase(it);
			break;
		}
	}
}
void Engine::EventManager::UnSurscribe	(EventHandler * eventHandler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	//Iterate through map.
	for (std::map<int, EventHandler*>::iterator it = m_EventHandlerEvents.begin(); it != m_EventHandlerEvents.end();) {
		//Check is value equal.
		if ((it->second) == eventHandler) {
			//if equal delete and return element who is next. Do not increase pointer.
			it = m_EventHandlerEvents.erase(it);
		} else {
			//If data not equal increase pointer to go through map.
			it++;
		}
	}
}

	/*
	 * Store event for procces optimization
	 * to loop trought surscribers only one time
	 * insted of looping everytime we send event.
	 */
void Engine::EventManager::SendEvent	(BasicEvent * event) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Events.push_back(event);
}

	/*
	 * Not optimal because we everytime send event
	 * we have to loop throught m_EventHandlerEvents map.
	 */
void Engine::EventManager::SendEventNow (BasicEvent * event) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	/* Store 2 pointers from map. First pointer stores address where stars objects with key value,
	 * second stores addres where ends objects with key value.
	 */
	std::pair<std::multimap<int, EventHandler*>::iterator, std::multimap<int, EventHandler*>::iterator> range;
	/*
	 * Get by object range in map.
	 */
	range = m_EventHandlerEvents.equal_range(event->GetType());
	/*
	 * Iterate thought map in specific range.
	 */
	for (std::multimap<int, EventHandler*>::iterator it = range.first; it != range.second; it++) {
		//Send subscripted event to event handler.
		if (it->second->OnEvent(*event)) {
			break;
		}
	}
	//Release memory.
	delete event;
}

void Engine::EventManager::Update() {
	std::lock_guard<std::mutex> lock(m_Mutex);
	/*Lock for multithread*/
	for (int i = 0; i < m_Events.size(); i++) {
		/* Store 2 pointers from map. First pointer stores address where stars objects with key value,
			* second stores addres where ends objects with key value.
			*/
		std::pair<std::multimap<int, EventHandler*>::iterator, std::multimap<int, EventHandler*>::iterator> range;
		/*
			* Get by object range in map.
			*/
		int id = m_Events[i]->GetType();
		range = m_EventHandlerEvents.equal_range(id);
		/*
			* Iterate thought map in specific range.
			*/
		for (std::multimap<int, EventHandler*>::iterator it = range.first; it != range.second; it++) {
			//Send subscripted event to event handler.
			if (it->second->OnEvent(*m_Events[i])) {
				break;
			}
		}
		//Delete event/free memory
		delete m_Events[i];
	}
	m_Events.clear();
}