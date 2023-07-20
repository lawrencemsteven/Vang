#pragma once

#include "Vang/Window/Window.h"

#include "GLFW/glfw3.h"

namespace Vang {

	class WindowGLFW : public Window {
	public:
		WindowGLFW();
		WindowGLFW(std::string_view title);
		WindowGLFW(uint32_t width, uint32_t height);
		WindowGLFW(std::string_view title, uint32_t width, uint32_t height);
		~WindowGLFW();
		WindowGLFW(const WindowGLFW&)	  = delete;
		WindowGLFW(WindowGLFW&&)		  = delete;
		WindowGLFW& operator=(const WindowGLFW&) = delete;
		WindowGLFW& operator=(WindowGLFW&&)		 = delete;

		void beginFrame() override;
		void close() override;

		const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const override;

		void setTitle(std::string_view title) override;

		void setResolution(uint32_t width, uint32_t height) override;

		void resize(int width, int height);
		void mouseCallback(double xpos, double ypos);

	private:
		void initializeWindow();
		static void resize(GLFWwindow* window, int width, int height);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		GLFWwindow* m_window;
	};

}