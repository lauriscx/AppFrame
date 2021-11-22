//#include "DEnginePch.h"
#include "EventHandler.h"
#include "EventManager.h"


/* Add priority support for receiving events */

Engine::EventHandler::EventHandler() : m_Name("Event handler empty") {}
Engine::EventHandler::EventHandler(const char * name) : m_Name(name) {}

void Engine::EventHandler::SubscribeToEvent		(int eventType) {
	EventManager::GetInstance()->Surscribe(eventType, this);
}
void Engine::EventHandler::UnsubscribeToEvent	(int eventType) {
	EventManager::GetInstance()->UnSurscribe(eventType, this);
}
void Engine::EventHandler::UnsubscribeToEvents	() {
	EventManager::GetInstance()->UnSurscribe(this);
}

const char * Engine::EventHandler::GetHandlerName() {
	return m_Name.c_str();
}

Engine::EventHandler::~EventHandler() {
	UnsubscribeToEvents();
}