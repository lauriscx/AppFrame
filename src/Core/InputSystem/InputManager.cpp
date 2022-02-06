#include "InputManager.h"
#include "InputHandler.h"

AppFrame::InputManager* AppFrame::InputManager::s_Instance = new AppFrame::InputManager();

bool AppFrame::InputManager::IsKeyPressed(Key key) {
	std::lock_guard<std::mutex> lock(m_Mutex);

	return m_Keys[key];
}

bool AppFrame::InputManager::IsButtonPressed(Key Button) {
	std::lock_guard<std::mutex> lock(m_Mutex);

	return m_Keys[Button];
}

std::pair<float, float> AppFrame::InputManager::GetMousePosition() {
	std::lock_guard<std::mutex> lock(m_Mutex);

	return m_MousePosition;
}

void AppFrame::InputManager::SendInput(const InputData& input) {
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (input.action >= 0 && input.key >= 0) {
		m_Keys[input.key] = input.action;
	}

	if (input.Mouse) {
		m_MousePosition = std::pair<int, int>(input.x, input.y);
	}

	for (std::vector<InputHandler*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++) {
		if ((*it)->OnInput(input)) {
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