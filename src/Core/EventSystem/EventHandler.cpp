//#include "DEnginePch.h"
#include "EventHandler.h"
#include "EventManager.h"


/* Add priority support for receiving events */

AppFrame::EventHandler::EventHandler() : m_Name("Event handler empty") {}
AppFrame::EventHandler::EventHandler(const char * name) : m_Name(name) {}

void AppFrame::EventHandler::SubscribeToEvent		(int eventType) {
	EventManager::GetInstance()->Surscribe(eventType, this);
}
void AppFrame::EventHandler::UnsubscribeToEvent	(int eventType) {
	EventManager::GetInstance()->UnSurscribe(eventType, this);
}
void AppFrame::EventHandler::UnsubscribeToEvents	() {
	EventManager::GetInstance()->UnSurscribe(this);
}

const char * AppFrame::EventHandler::GetHandlerName() {
	return m_Name.c_str();
}

AppFrame::EventHandler::~EventHandler() {
	UnsubscribeToEvents();
}