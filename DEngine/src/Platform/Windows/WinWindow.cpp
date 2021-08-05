#include "DEnginePch.h"
#include "WinWindow.h"
#include "glfw3.h"
#include "Core/InputSystem/InputManager.h"
#include "Core/EventSystem/EventManager.h"
#include "Application/Events/AppEvents.h"

Engine::WinWindow::WinWindow() : windowClosed(false) { }

bool Engine::WinWindow::Create() {

	/* Initialize the library */
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);

	if (!m_Window) {
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent((GLFWwindow*)m_Window);

	glfwSetWindowUserPointer((GLFWwindow*)m_Window, &windowClosed);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int width, int height) {
		EventManager::GetInstance()->SendEventNow(new WindowResize(width, height));
	});

	glfwSetWindowCloseCallback((GLFWwindow*)m_Window, [](GLFWwindow* window) {
		EventManager::GetInstance()->SendEventNow(new WindowCloses());
	});


	glfwSetKeyCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputManager::GetInstance()->SendInput(0, 0, action, key);
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS: {
			KeyPressedEvent* event = new KeyPressedEvent(key, 0);
			events->AddEvent(event);
			break;
		} case GLFW_RELEASE: {
			KeyReleasedEvent* event = new KeyReleasedEvent(key);
			events->AddEvent(event);
			break;
		} case GLFW_REPEAT: {
			KeyPressedEvent* event = new KeyPressedEvent(key, 1);
			events->AddEvent(event);
			break;
		}
		}*/
	});

	glfwSetCharCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, unsigned int keycode) {
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);
		KeyTypedEvent* e = new KeyTypedEvent(keycode);
		events->AddEvent(e);*/
	});

	glfwSetMouseButtonCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		InputManager::GetInstance()->SendInput(0, 0, action, button);
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS: {
			MausePressedEvent* event = new MausePressedEvent(button);
			events->AddEvent(event);
			break;
		} case GLFW_RELEASE: {
			MauseReleaseEvent* event = new MauseReleaseEvent(button);
			events->AddEvent(event);
			break;
		}
		}*/
	});

	glfwSetScrollCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, double x, double y) {
		InputManager::GetInstance()->SendInput((int)x, (int)y, -1, 0);
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		MauseScrollEvent* event = new MauseScrollEvent(x, y);
		events->AddEvent(event);*/
	});

	glfwSetCursorPosCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, double x, double y) {
		InputManager::GetInstance()->SendInput((int)x, (int)y, 0, 0);
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		MauseCursorEvent* event = new MauseCursorEvent(x, y);
		events->AddEvent(event);*/
	});


	return true;
}

void Engine::WinWindow::SetTitle(const char * title) {
	this->title = title;
}

void Engine::WinWindow::SetWidth(int width) {
	this->width = width;
}

void Engine::WinWindow::SetHeight(int height) {
	this->height = height;
}

void Engine::WinWindow::SetVSync(bool vsync) {
	glfwSwapInterval(1);
	this->vsync = vsync;
}

const char * Engine::WinWindow::GetTitle() {
	return title;
}

int Engine::WinWindow::GetWidth() const {
	return width;
}

int Engine::WinWindow::GetHeight() const {
	return height;
}

bool Engine::WinWindow::GetVSync() const {
	return vsync;
}

void Engine::WinWindow::OnUpdate() {
	glfwSwapBuffers((GLFWwindow*)m_Window);
	glfwPollEvents();
}

bool Engine::WinWindow::Closed() {
	return windowClosed;
}

Engine::WinWindow::~WinWindow() {
	glfwTerminate();
	glfwDestroyWindow((GLFWwindow*)m_Window);
}