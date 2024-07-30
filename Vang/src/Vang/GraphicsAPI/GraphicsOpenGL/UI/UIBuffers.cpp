#include "UIBuffers.h"

namespace Vang::gfx::OpenGL::UI {

	UIBuffers::~UIBuffers() {}

	void UIBuffers::initialize() {
		m_coloredPanelBuffer.initialize();
	}

	void UIBuffers::update() {
		m_coloredPanelBuffer.update();
	}

}