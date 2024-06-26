#include "Vang.h"
#include "Vang/Window/WindowGLFW/WindowGLFW.h"

#include "Vang/Utility/Input/Input.h"
#include "Vang/Utility/Events/MouseEvent.h"
#include "Vang/Utility/Events/ApplicationEvent.h"
#include "Vang/Utility/Events/KeyEvent.h"
#include "WindowGLFW.h"

namespace Vang::Windowing {

	WindowGLFW::~WindowGLFW() {
		close();
	}

	void WindowGLFW::initialize(const std::string& title, uint32_t width, uint32_t height,
								bool fullscreen) {
		Window::initialize(title, width, height, fullscreen);
		initializeWindow();
	}

	void WindowGLFW::update() {
		if (glfwWindowShouldClose(m_window))
			Vang::close();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void WindowGLFW::close() {
		VANG_DEBUG("Closing GLFW Window");
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	const char** WindowGLFW::getGraphicsAPIInstanceExtensions(uint32_t* count) const {
		return glfwGetRequiredInstanceExtensions(count);
	}

	void WindowGLFW::setTitle(const std::string& title) {
		VANG_FATAL("NOT YET IMPLEMENTED!");
	}

	void WindowGLFW::setResolution(uint32_t width, uint32_t height) {
		VANG_FATAL("NOT YET IMPLEMENTED!");
	}

	void WindowGLFW::setFullscreen(bool fullscreen) {
		VANG_FATAL("NOT YET IMPLEMENTED!");
	}

	void WindowGLFW::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_data.vSync = enabled;
	}

	void* WindowGLFW::getNativeWindow() const {
		return m_window;
	}

	void WindowGLFW::initializeWindow() {
		VANG_DEBUG("Initializing GLFW Window");
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

		if (m_data.fullscreen) {
			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.data(),
										glfwGetPrimaryMonitor(), nullptr);
		}
		else {
			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.data(), nullptr,
										nullptr);
		}

		if (m_window == NULL) {
			VANG_FATAL("Failed to create GLFW Window!");
		}

		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		setVSync(m_data.vSync);
		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSetFramebufferSizeCallback(m_window, resizeCallback);
		glfwSetWindowCloseCallback(m_window, closeCallback);
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetCharCallback(m_window, charCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
		glfwSetScrollCallback(m_window, mouseScrollCallback);
		glfwSetCursorPosCallback(m_window, mouseMoveCallback);
	}

	void WindowGLFW::resizeCallback(GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width		 = width;
		data.height		 = height;

		Vang::Utility::Events::WindowResizeEvent event{static_cast<unsigned int>(width),
													   static_cast<unsigned int>(height)};
		data.eventCallback(event);
	}

	void WindowGLFW::closeCallback(GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		Vang::Utility::Events::WindowCloseEvent event{};
		data.eventCallback(event);
	}

	void WindowGLFW::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {
			case GLFW_PRESS: {
				Vang::Utility::Events::KeyPressedEvent event{static_cast<Vang::Input::KEY>(key), 0};
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				Vang::Utility::Events::KeyReleasedEvent event{static_cast<Vang::Input::KEY>(key)};
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				Vang::Utility::Events::KeyPressedEvent event{static_cast<Vang::Input::KEY>(key), 1};
				data.eventCallback(event);
				break;
			}
		}
	}

	void WindowGLFW::charCallback(GLFWwindow* window, unsigned int keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		Vang::Utility::Events::KeyTypedEvent event{static_cast<Vang::Input::KEY>(keycode)};
		data.eventCallback(event);
	}

	void WindowGLFW::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {
			case GLFW_PRESS: {
				Vang::Utility::Events::MouseButtonPressedEvent event{
					static_cast<Vang::Input::MOUSE>(button)};
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				Vang::Utility::Events::MouseButtonReleasedEvent event{
					static_cast<Vang::Input::MOUSE>(button)};
				data.eventCallback(event);
				break;
			}
		}
	}

	void WindowGLFW::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		Vang::Utility::Events::MouseScrolledEvent event{static_cast<float>(xOffset),
														static_cast<float>(yOffset)};
		data.eventCallback(event);
	}

	void WindowGLFW::mouseMoveCallback(GLFWwindow* window, double xOffset, double yOffset) {
		Window::WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

		Vang::Utility::Events::MouseMovedEvent event{static_cast<float>(xOffset),
													 static_cast<float>(yOffset)};
		data.eventCallback(event);
	}
}