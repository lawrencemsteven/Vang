#include "Vang.h"
#include "UIManager.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Vang::UI {

	UIManager::~UIManager() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void UIManager::initialize() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// IF using Docking Branch
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Multiple Viewports

		ImGui::StyleColorsDark();
		// ImGui::StyleColorsLight();

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Vang::getWindow().getNativeWindow()),
									 true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void UIManager::update() {
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Draw the menu if it is not hidden
		for (auto& iter : m_menus) {
			if (iter->getDrawMenu()) {
				iter->draw();
			}
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update Viewports
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	std::shared_ptr<ImGuiMenu> UIManager::pushImGuiMenu(std::shared_ptr<ImGuiMenu> menu) {
		m_menus.push_back(menu);
		menu->onAttach();
		return m_menus.back();
	}

	void UIManager::popImGuiMenu(std::shared_ptr<ImGuiMenu> menu) {
		auto it = std::find(m_menus.begin(), m_menus.end(), menu);
		if (it != m_menus.end()) {
			m_menus.erase(it);
		}
	}
}