#include "InputHandler.h"
#include "InputManager.h"


Engine::InputHandler::InputHandler() {
	Engine::InputManager::GetInstance()->AddHandler(this);
}

Engine::InputHandler::~InputHandler() {
	Engine::InputManager::GetInstance()->RemoveHandler(this);
}