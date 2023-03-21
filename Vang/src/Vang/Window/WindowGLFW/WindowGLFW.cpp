#include "Vang.h"
#include "Vang/Window/WindowGLFW/WindowGLFW.h"

namespace Vang {

	WindowGLFW::WindowGLFW()
		: Window() {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(std::string_view title)
		: Window(title) {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(uint32_t width, uint32_t height)
		: Window(width, height) {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(std::string_view title, uint32_t width, uint32_t height)
		: Window(title, width, height) {
		initializeWindow();
	}

	WindowGLFW::~WindowGLFW() { close();
	}

	void WindowGLFW::beginFrame() {
		if (glfwWindowShouldClose(m_window)) VangInst::Get().toClose();

		glfwPollEvents();
	}

	void WindowGLFW::close() {
		if (windowOpen) {
			windowOpen = false;
			VANG_DEBUG("Closing GLFW Window");
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}

	void WindowGLFW::setTitle(std::string_view title) { VANG_FATAL("NOT YET IMPLEMENTED!"); }

	void WindowGLFW::setResolution(uint32_t width, uint32_t height) {
		VANG_FATAL("NOT YET IMPLEMENTED!");
	}

	void WindowGLFW::initializeWindow() {
		VANG_DEBUG("Initializing GLFW Window");
		windowOpen = true;
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(m_width, m_height, m_title.data(), nullptr, nullptr);
	}
}