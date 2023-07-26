#pragma once

#include "Vang/Window/Window.h"

#include "GLFW/glfw3.h"

namespace Vang {

	class WindowGLFW : public Window {
	public:
		WindowGLFW(const std::string& title, uint32_t width, uint32_t height);
		~WindowGLFW();
		WindowGLFW(const WindowGLFW&)	  = delete;
		WindowGLFW(WindowGLFW&&)		  = delete;
		WindowGLFW& operator=(const WindowGLFW&) = delete;
		WindowGLFW& operator=(WindowGLFW&&)		 = delete;

		void update() override;
		void close() override;

		const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const override;

		void setTitle(const std::string& title) override;
		void setResolution(uint32_t width, uint32_t height) override;
		void setEventCallback(const EventCallbackFn& callback) override;
		void setVSync(bool enabled) override;

		void* getNativeWindow() const override;

	private:
		void initializeWindow();
		static void resizeCallback(GLFWwindow* window, int width, int height);
		static void closeCallback(GLFWwindow* window);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charCallback(GLFWwindow* window, unsigned int keycode);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static void mouseMoveCallback(GLFWwindow* window, double xOffset, double yOffset);

		GLFWwindow* m_window;
	};

}