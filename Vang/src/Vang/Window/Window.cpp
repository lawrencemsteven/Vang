#include "Vang/Window/Window.h"

namespace Vang {

	Window::Window(const std::string& title, uint32_t width, uint32_t height) {
		m_data.title  = title;
		m_data.width  = width;
		m_data.height = height;
		m_data.vSync  = false;
	}

	const std::string& Window::getTitle() const {
		return m_data.title;
	}

	uint32_t Window::getWidth() const {
		return m_data.width;
	}

	uint32_t Window::getHeight() const {
		return m_data.height;
	}

	bool Window::getVSync() const {
		return m_data.vSync;
	}

}
