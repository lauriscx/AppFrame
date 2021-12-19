#include "InputManager.h"
#include "InputHandler.h"

AppFrame::InputManager* AppFrame::InputManager::s_Instance = new AppFrame::InputManager();

void AppFrame::InputManager::SendInput(int x, int y, int action, int key) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (std::vector<InputHandler*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++) {
		if ((*it)->OnInput(x, y, action, key)) {
			break;
		}
	}
}

void AppFrame::InputManager::AddHandler(InputHandler* handler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Handlers.push_back(handler);
}

void AppFrame::InputManager::RemoveHandler(InputHandler * handler) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (std::vector<InputHandler*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++) {
		if ((*it) == handler) {
			m_Handlers.erase(it);
			break;
		}
	}
}