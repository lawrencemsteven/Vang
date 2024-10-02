#pragma once

#include "Menu.h"

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

		std::shared_ptr<Menu> pushMenu(std::shared_ptr<Menu> menu);

		void popMenu(std::shared_ptr<Menu> menu);

	private:
		std::vector<std::shared_ptr<Menu>> m_menus;
	};

}