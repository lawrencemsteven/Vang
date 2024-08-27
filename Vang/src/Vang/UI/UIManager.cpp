#include "UIManager.h"

namespace Vang::UI {

	void UIManager::update() {
		for (auto& iter : m_menuIds) {
			iter.second.update();
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