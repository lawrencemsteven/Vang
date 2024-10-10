#include <Vang.h>
#include <imgui.h>

class DemoMenu : public Vang::UI::Menu {
public:
	void draw() override {
		ImGui::ShowDemoWindow(&m_drawMenu);
	}
};

class FPSOverlay : public Vang::UI::Menu {
	void draw() override {
		static int location = 1;
		ImGuiIO& io			= ImGui::GetIO();
		ImGuiWindowFlags window_flags =
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		if (location >= 0) {
			const float PAD				  = 10.0f;
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImVec2 work_pos =
				viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
			ImVec2 work_size = viewport->WorkSize;
			ImVec2 window_pos, window_pos_pivot;
			window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
			window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
			window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
			window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
			ImGui::SetNextWindowViewport(viewport->ID);
			window_flags |= ImGuiWindowFlags_NoMove;
		}
		else if (location == -2) {
			// Center window
			ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always,
									ImVec2(0.5f, 0.5f));
			window_flags |= ImGuiWindowFlags_NoMove;
		}
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		if (ImGui::Begin("Example: Simple overlay", &m_drawMenu, window_flags)) {

			ImGui::Text("%6.1ffps", io.Framerate);

			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("Custom", NULL, location == -1))
					location = -1;
				if (ImGui::MenuItem("Center", NULL, location == -2))
					location = -2;
				if (ImGui::MenuItem("Top-left", NULL, location == 0))
					location = 0;
				if (ImGui::MenuItem("Top-right", NULL, location == 1))
					location = 1;
				if (ImGui::MenuItem("Bottom-left", NULL, location == 2))
					location = 2;
				if (ImGui::MenuItem("Bottom-right", NULL, location == 3))
					location = 3;
				if (&m_drawMenu && ImGui::MenuItem("Close"))
					m_drawMenu = false;
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
};

class SampleMenu : public Vang::UI::Menu {
public:
	void onAttach() override {
		demoMenu->setDrawMenu(false);
		Vang::getUIManager().pushMenu(demoMenu);
		Vang::getUIManager().pushMenu(fpsOverlay);
	}

	void onDetach() override {
		Vang::getUIManager().popMenu(demoMenu);
		Vang::getUIManager().pushMenu(fpsOverlay);
	}

	void draw() override {
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Begin("Main Menu");

		ImGui::Checkbox("Demo Window", &demoMenu->getDrawMenu());
		ImGui::Checkbox("FPS Overlay", &fpsOverlay->getDrawMenu());

		const char* displayModes[]	  = {"Windowed", "Borderless", "Fullscreen"};
		static int currentDisplayMode = 0;
		if (ImGui::Combo("Display Mode", &currentDisplayMode, displayModes,
						 IM_ARRAYSIZE(displayModes))) {
			switch (currentDisplayMode) {
				case 0:
					Vang::getWindow().setDisplayMode(Vang::Windowing::DISPLAY_MODE::WINDOWED);
					break;
				case 1:
					Vang::getWindow().setDisplayMode(Vang::Windowing::DISPLAY_MODE::BORDERLESS);
					break;
				case 2:
					Vang::getWindow().setDisplayMode(Vang::Windowing::DISPLAY_MODE::FULLSCREEN);
					break;
			}
		}

		const char* displayResolutions[]	= {"1280x720", "1920x1080", "3440x1440"};
		static int currentDisplayResolution = 1;
		if (ImGui::Combo("Display Resolution", &currentDisplayResolution, displayResolutions,
						 IM_ARRAYSIZE(displayResolutions))) {
			switch (currentDisplayResolution) {
				case 0: Vang::getWindow().setResolution(1280, 720); break;
				case 1: Vang::getWindow().setResolution(1920, 1080); break;
				case 2: Vang::getWindow().setResolution(3440, 1440); break;
			}
		}

		ImGui::End();
	}

private:
	std::shared_ptr<DemoMenu> demoMenu	   = std::make_shared<DemoMenu>();
	std::shared_ptr<FPSOverlay> fpsOverlay = std::make_shared<FPSOverlay>();
};