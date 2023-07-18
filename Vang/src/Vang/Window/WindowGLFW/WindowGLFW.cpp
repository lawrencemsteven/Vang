#include "Vang.h"
#include "Vang/Window/WindowGLFW/WindowGLFW.h"

#include "Vang/Utility/Input/Input.h"

namespace Vang {

	WindowGLFW::WindowGLFW(VangInst& vangInst)
		: Window(vangInst) {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(VangInst& vangInst, std::string_view title)
		: Window(vangInst, title) {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(VangInst& vangInst, uint32_t width, uint32_t height)
		: Window(vangInst, width, height) {
		initializeWindow();
	}

	WindowGLFW::WindowGLFW(VangInst& vangInst, std::string_view title, uint32_t width,
						   uint32_t height)
		: Window(vangInst, title, width, height) {
		initializeWindow();
	}

	WindowGLFW::~WindowGLFW() { close(); }

	void WindowGLFW::beginFrame() {
		if (glfwWindowShouldClose(m_window)) m_vangInst.toClose();

		glfwSwapBuffers(m_window);
		glfwPollEvents();


	}

	void WindowGLFW::close() {
		if (m_windowOpen) {
			m_windowOpen = false;
			VANG_DEBUG("Closing GLFW Window");
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}

	const char** WindowGLFW::getGraphicsAPIInstanceExtensions(uint32_t* count) const {
		return glfwGetRequiredInstanceExtensions(count);
	}

	void WindowGLFW::setTitle(std::string_view title) { VANG_FATAL("NOT YET IMPLEMENTED!"); }

	void WindowGLFW::setResolution(uint32_t width, uint32_t height) {
		VANG_FATAL("NOT YET IMPLEMENTED!");
	}

	void WindowGLFW::initializeWindow() {
		VANG_DEBUG("Initializing GLFW Window");
		m_windowOpen = true;
		glfwInit();

#ifdef VANG_GRAPHICSAPI_OPENGL
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#elif VANG_GRAPHICSAPI_VULKAN
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

		m_window = glfwCreateWindow(m_width, m_height, m_title.data(), nullptr, nullptr);

		if (m_window == NULL) { VANG_FATAL("Failed to create GLFW Window!"); }

		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, resize);
		glfwSetCursorPosCallback(m_window, mouseCallback);
	}

	void WindowGLFW::resize(int width, int height) {
		m_width	 = width;
		m_height = height;
		m_vangInst.getGraphicsAPI().windowResize(static_cast<uint32_t>(width),
												 static_cast<uint32_t>(height));
	}

	void WindowGLFW::mouseCallback(double x_pos, double y_pos) {
		m_vangInst.getPlayer().getCamera().mouseRotate(x_pos, y_pos);
	}

	void WindowGLFW::resize(GLFWwindow* window, int width, int height) {
		WindowGLFW* windowGLFW = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		windowGLFW->resize(width, height);
	}

	void WindowGLFW::mouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
		WindowGLFW* windowGLFW = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		windowGLFW->mouseCallback(x_pos, y_pos);
	}
}