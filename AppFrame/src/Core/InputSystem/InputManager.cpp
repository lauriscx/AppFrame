#include "InputManager.h"
#include "InputHandler.h"

Engine::InputManager* Engine::InputManager::s_Instance = new Engine::InputManager();

void Engine::InputManager::SendInput(int x, int y, int action, int key) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (std::vector<InputHandler*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++) {
		if ((*it)->OnInput(x, y, action, key)) {
			break;
		}
	}
}

void Engine::InputManager::AddHandler(InputHandler* handler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Handlers.push_back(handler);
}

void Engine::InputManager::RemoveHandler(InputHandler * handler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (std::vector<InputHandler*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++) {
		if ((*it) == handler) {
			m_Handlers.erase(it);
			break;
		}
	}
}