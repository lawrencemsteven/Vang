#pragma once

#include "Buffers/ColoredPanelBuffer.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL::UI {

	class UIBuffers {
	public:
		UIBuffers() = default;
		~UIBuffers();

		void initialize();
		void update();

	private:
		Buffers::ColoredPanelBuffer m_coloredPanelBuffer{};
	};

}