#pragma once

#include "Vang/GraphicsAPI/Generic/Components.h"

namespace Vang::UI {

	class Menu {
	public:
		Menu();
		~Menu()						 = default;
		Menu(const Menu&)			 = delete;
		Menu(Menu&&)				 = default;
		Menu& operator=(const Menu&) = delete;
		Menu& operator=(Menu&&)		 = default;

		bool getHidden() const;

		void setHidden(bool hidden);

		gfx::Generic::Buffers::UI::ColoredPanelBuffer::ColoredPanelID
		addPanel(const glm::vec2& topLeft, const glm::vec2& bottomRight, const float depth,
				 const glm::vec4& color);

		void removePanel(gfx::Generic::Buffers::UI::ColoredPanelBuffer::ColoredPanelID idx);

		void update();

	private:
		std::unique_ptr<Vang::gfx::Generic::Buffers::UI::ColoredPanelBuffer> m_coloredPanelBuffer;

		bool m_hidden{false};
	};

}