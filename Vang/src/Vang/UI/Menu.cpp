#include "Menu.h"

namespace Vang::UI {

	Menu::Menu() {
		m_coloredPanelBuffer = Vang::gfx::Components::getColoredPanelBuffer();
		m_coloredPanelBuffer->initialize();
	}

	bool Menu::getHidden() const {
		return m_hidden;
	}

	void Menu::setHidden(bool hidden) {
		m_hidden = hidden;
	}

	gfx::Generic::Buffers::UI::ColoredPanelBuffer::ColoredPanelID
	Menu::addPanel(const glm::vec2& topLeft, const glm::vec2& bottomRight, const float depth,
				   const glm::vec4& color) {
		return m_coloredPanelBuffer->addPanel(topLeft, bottomRight, depth, color);
	}

	void Menu::removePanel(gfx::Generic::Buffers::UI::ColoredPanelBuffer::ColoredPanelID idx) {
		m_coloredPanelBuffer->removePanel(idx);
	}

	void Menu::update() {
		if (!m_hidden) {
			m_coloredPanelBuffer->update();
		}
	}

}