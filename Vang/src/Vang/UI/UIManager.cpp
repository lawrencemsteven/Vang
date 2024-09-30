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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // IF using Docking Branch
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // Multiple Viewports

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

		static bool show_demo_window	= true;
		static bool show_another_window = true;
		static ImVec4 clear_color		= ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (show_demo_window) {
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		if (show_another_window) {
			static float f	   = 0.0f;
			static int counter = 0;

			ImGui::Begin(
				"Hello, world!"); // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text."); // Display some text (you can use a format
													  // strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);

			ImGui::SliderFloat("float", &f, 0.0f,
							   1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color",
							  (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return
										 // true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
						io.Framerate);
			ImGui::End();
		}

		// for (auto& iter : m_menuIds) {
		// 	iter.second.update();
		// }

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	Menu& UIManager::getMenu(std::size_t menuId) {
		return m_menuIds.at(menuId);
	}

	std::size_t UIManager::createMenu() {
		m_menuIds[m_menuIdCounter];

		const auto output = m_menuIdCounter;

		while (m_menuIds.find(m_menuIdCounter) != m_menuIds.end()) {
			m_menuIdCounter += 1;
		}

		return output;
	}

	void UIManager::removeMenu(std::size_t menuId) {
		m_menuIds.erase(menuId);
	}
}