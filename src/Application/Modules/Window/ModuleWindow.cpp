//#include "DEnginePch.h"
#include "Application/Modules/Window/ModuleWindow.h"
#include "Application/Events/AppEvents.h"
#include "Core/InputSystem/InputManager.h"
#include "Core/EventSystem/EventManager.h"
#include "glfw3.h"

#include <iostream>

bool AppFrame::ModuleWindow::Minimized = false;

AppFrame::ModuleWindow::ModuleWindow() { }
void AppFrame::ModuleWindow::OnStart() {

	/* Initialize the library */
	if (!glfwInit()) {
		Fatal("ModuleWindow", __FILE__, __LINE__, "Failed to init GLFW");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // We don't want the old OpenGL 
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(m_Context->GetWindowWidth(), m_Context->GetWindowHeight(), m_Context->GetApplicationName().c_str(), NULL, NULL);

	if (!m_Window) {
		glfwTerminate();
		Fatal("ModuleWindow", __FILE__, __LINE__, "Failed to create window");
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent((GLFWwindow*)m_Window);

	glfwSwapInterval(m_Context->GetFPSLimit());

	//glfwSetWindowUserPointer((GLFWwindow*)m_Window, &windowClosed);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int width, int height) {
		if (width == 0 && height == 0) {
			EventManager::GetInstance()->SendEventNow(new WindowMinimized());
			Minimized = true;
		} else {
			if (Minimized) {
				EventManager::GetInstance()->SendEventNow(new WindowMaximized());
				Minimized = false;
			}
			EventManager::GetInstance()->SendEventNow(new WindowResize(width, height));
		}
	});

	glfwSetWindowCloseCallback((GLFWwindow*)m_Window, [](GLFWwindow* window) {
		EventManager::GetInstance()->SendEventNow(new WindowCloses());
	});


	glfwSetKeyCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		
		InputManager::GetInstance()->SendInput({ -1, -1, action, (Key)key });
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
		InputManager::GetInstance()->SendInput({ -1, -1, (action == GLFW_PRESS || action == GLFW_REPEAT), (Key)button });
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
		InputManager::GetInstance()->SendInput({ (int)x, (int)y, -1, (Key)0 });
		EventManager::GetInstance()->SendEventNow(new InputScroll(x, y));
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		MauseScrollEvent* event = new MauseScrollEvent(x, y);
		events->AddEvent(event);*/
	});

	glfwSetCursorPosCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, double x, double y) {
		InputManager::GetInstance()->SendInput({ (int)x, (int)y, 0, (Key)0 });
		/*Events* events = (Events*)glfwGetWindowUserPointer(window);

		MauseCursorEvent* event = new MauseCursorEvent(x, y);
		events->AddEvent(event);*/
	});
	return;
}

void AppFrame::ModuleWindow::OnEarlyUpdate(float deltaTime) {
	glfwPollEvents();
}



void AppFrame::ModuleWindow::OnUpdate(float deltaTime) {

}

void AppFrame::ModuleWindow::OnLateUpdate(float deltaTime) {
	glfwSwapBuffers((GLFWwindow*)m_Window);
}

void AppFrame::ModuleWindow::OnStop() {
	glfwTerminate();
	glfwDestroyWindow((GLFWwindow*)m_Window);
	if (m_Window) {
		//delete m_Window;
	}
}

AppFrame::ModuleWindow::~ModuleWindow() {
}