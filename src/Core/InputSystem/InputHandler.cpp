#include "InputHandler.h"
#include "InputManager.h"


AppFrame::InputHandler::InputHandler() {
	AppFrame::InputManager::GetInstance()->AddHandler(this);
}

AppFrame::InputHandler::~InputHandler() {
	AppFrame::InputManager::GetInstance()->RemoveHandler(this);
}