#include "ModuleIMGUI.h"
#include "Application/Application.h"
#include "Application/Modules/Window/ModuleWindow.h"
#include "Application/Events/Log.h"
#include "Application/Logger.h"

#include "glew.h"

// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


AppFrame::ModuleIMGUI::ModuleIMGUI() {}

void AppFrame::ModuleIMGUI::OnStart() {	
	GLFWwindow * window = static_cast<GLFWwindow*>(static_cast<ModuleWindow*>(Application::GetInstance()->GetModule<ModuleWindow>())->GetWindow());
	if (!window) {
		FATAL("IMGUI", "Window not created or window module not exist!");
		return;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::SetCurrentContext(context);
}

void AppFrame::ModuleIMGUI::OnEarlyUpdate(float deltaTime) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void AppFrame::ModuleIMGUI::OnUpdate(float deltaTime) {
	//bool show = true;
	//ImGui::ShowDemoWindow(&show);
}

void AppFrame::ModuleIMGUI::OnLateUpdate(float deltaTime) {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void AppFrame::ModuleIMGUI::OnAppInput(const InputData& input)
{
}

void AppFrame::ModuleIMGUI::OnAppEvent(BasicEvent * event)
{
}

void AppFrame::ModuleIMGUI::OnStop() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

AppFrame::ModuleIMGUI::~ModuleIMGUI()
{
}
