#pragma once

#include "Vang/Window/Window.h"
#include "Vang/Window/WindowGLFW/GLFWInputCache.h"

#include "GLFW/glfw3.h"

namespace Vang::Windowing {

	class WindowGLFW : public Window {
	public:
		WindowGLFW() = default;
		~WindowGLFW();
		WindowGLFW(const WindowGLFW&)			 = delete;
		WindowGLFW(WindowGLFW&&)				 = delete;
		WindowGLFW& operator=(const WindowGLFW&) = delete;
		WindowGLFW& operator=(WindowGLFW&&)		 = delete;

		void initialize(const std::string& title, uint32_t width, uint32_t height,
						bool fullscreen) override;
		void update() override;
		void close() override;

		const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const override;

		void setTitle(const std::string& title) override;
		void setResolution(uint32_t width, uint32_t height) override;
		void setFullscreen(bool fullscreen) override;
		void setVSync(bool enabled) override;
		void setMouseEnabled(bool enabled) override;

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

		double m_prevMouseX{0.0};
		double m_prevMouseY{0.0};

		GLFWwindow* m_window;
	};

}