#include "Vang/Window/Window.h"

namespace Vang {

	Window::Window()
		: m_title{""},
		  m_width{1280},
		  m_height{720} {}

	Window::Window(std::string_view title)
		: m_title{title},
		  m_width{1280},
		  m_height{720} {}

	Window::Window(uint32_t width, uint32_t height)
		: m_title{""},
		  m_width{width},
		  m_height{height} {}

	Window::Window(std::string_view title, uint32_t width, uint32_t height)
		: m_title{title},
		  m_width{width},
		  m_height{height} {}

	const std::string_view& Window::getTitle() const { return m_title; }

	uint32_t Window::getWidth() const { return m_width; }

	uint32_t Window::getHeight() const { return m_height; }



}
