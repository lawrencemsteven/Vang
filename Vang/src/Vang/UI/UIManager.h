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

		Menu& getMenu(std::size_t menuId);

		std::size_t createMenu();

		void removeMenu(std::size_t menuId);

	private:
		std::unordered_map<std::size_t, Menu> m_menuIds;
		std::size_t m_menuIdCounter = 0;
	};

}