#pragma once
#include "Core/Core.h"
#include <map>
#include <vector>
#include <mutex>
#include "Core/InputSystem/InputData.h"

namespace AppFrame {
	class InputHandler;

	class InputManager {
	public:
		void OnButtonClick(int button) {}
		void OnButtonRelease(int button) {}
		void OnMouseMove(int x, int y) {}

		bool IsKeyPressed(Key key);
		bool IsButtonPressed(Key Button);
		std::pair<float, float> GetMousePosition();

		void SendInput(const InputData& input);

		void AddHandler(InputHandler* handler);
		void RemoveHandler(InputHandler* handler);

		static InputManager * GetInstance() { return s_Instance; }

	private:
		std::map<Key, bool> m_Keys;
		std::map<int, bool> m_Buttons;
		std::map<int, bool> m_ButtonsDown;
		std::map<int, bool> m_ButtonsUp;
		std::pair<int, int> m_MousePosition = { 0, 0 };

		std::vector<InputHandler*> m_Handlers;

		std::mutex m_Mutex;

		static InputManager * s_Instance;
	};
}