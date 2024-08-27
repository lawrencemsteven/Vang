#pragma once

#include "glm/glm.hpp"

namespace Vang::gfx::Generic::Buffers::UI {
	class ColoredPanelBuffer {
	public:
		typedef std::uint32_t ColoredPanelID;

		virtual void initialize() = 0;
		virtual void update()	  = 0;

		virtual ColoredPanelID addPanel(const glm::vec2& topLeft, const glm::vec2& bottomRight,
										const float depth, const glm::vec4& color) = 0;

		virtual void removePanel(ColoredPanelID idx) = 0;

	protected:
		std::uint32_t m_panelCount{0};
	};
}