#include "Vang/Window/Window.h"

#include "Vang.h"

namespace Vang::Windowing {

	void onEvent(Vang::Utility::Events::Event& e) {
		Vang::getEventHandler().onEvent(e);
	}

	Window::Window(const std::string& title, uint32_t width, uint32_t height) {
		m_data.title  = title;
		m_data.width  = width;
		m_data.height = height;
		m_data.eventCallback = &onEvent;
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
