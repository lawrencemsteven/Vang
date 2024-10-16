#pragma once

#include "ImGuiMenu.h"

namespace Vang::UI {

	class UIManager {
	public:
		UIManager() = default;
		~UIManager();
		UIManager(const UIManager&)			   = delete;
		UIManager(UIManager&&)				   = delete;
		UIManager& operator=(const UIManager&) = delete;
		UIManager& operator=(UIManager&&)	   = delete;

		void initialize();
		void update();

		std::shared_ptr<ImGuiMenu> pushImGuiMenu(std::shared_ptr<ImGuiMenu> menu);

		void popImGuiMenu(std::shared_ptr<ImGuiMenu> menu);

	private:
		std::vector<std::shared_ptr<ImGuiMenu>> m_menus;
	};

}