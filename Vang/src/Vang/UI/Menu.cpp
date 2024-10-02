#include "Menu.h"

namespace Vang::UI {

	bool Menu::getDrawMenu() const {
		return m_drawMenu;
	}

	bool& Menu::getDrawMenu() {
		return m_drawMenu;
	}

	void Menu::setDrawMenu(bool drawMenu) {
		m_drawMenu = drawMenu;
	}

}