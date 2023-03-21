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

		void beginFrame() override;
		void close() override;

		void setTitle(std::string_view title) override;

		void setResolution(uint32_t width, uint32_t height) override;

	private:
		void initializeWindow();

		GLFWwindow* m_window;
	};

}