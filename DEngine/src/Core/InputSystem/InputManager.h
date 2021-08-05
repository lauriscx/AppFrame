#pragma once
#include "Core/Core.h"
#include <map>
#include <vector>
#include <mutex>

namespace Engine {
	class InputHandler;

	class InputManager {
	public:
		void OnButtonClick(int button) {}
		void OnButtonRelease(int button) {}
		void OnMouseMove(int x, int y) {}

		void SendInput(int x, int y, int action, int key);

		void AddHandler(InputHandler* handler);
		void RemoveHandler(InputHandler* handler);

		static InputManager * GetInstance() { return s_Instance; }

	private:
		std::map<int, bool> m_Buttons;
		std::map<int, bool> m_ButtonsDown;
		std::map<int, bool> m_ButtonsUp;
		std::pair<int, int> m_MousePosition;

		std::vector<InputHandler*> m_Handlers;

		std::mutex m_Mutex;

		static InputManager * s_Instance;
	};
}