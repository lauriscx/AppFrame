#include "EventHandler.h"
#include "EventManager.h"

AppFrame::EventManager * AppFrame::EventManager::GetInstance() {
	static EventManager instance; return &instance;
}

void AppFrame::EventManager::Surscribe	(int eventType, EventHandler * eventHandler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_EventHandlerEvents.insert(std::make_pair(eventType, eventHandler));
}
void AppFrame::EventManager::UnSurscribe	(int eventType, EventHandler * eventHandler) {
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
void AppFrame::EventManager::UnSurscribe	(EventHandler * eventHandler) {
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
	 * Not optimal because we everytime send event
	 * we have to loop throught m_EventHandlerEvents map.
	 */
void AppFrame::EventManager::SendEvent(BasicEvent * event) {
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