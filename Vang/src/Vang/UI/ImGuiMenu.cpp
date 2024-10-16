#include "ImGuiMenu.h"

namespace Vang::UI {

	bool ImGuiMenu::getDrawMenu() const {
		return m_drawMenu;
	}

	bool& ImGuiMenu::getDrawMenu() {
		return m_drawMenu;
	}

	void ImGuiMenu::setDrawMenu(bool drawMenu) {
		m_drawMenu = drawMenu;
	}

}