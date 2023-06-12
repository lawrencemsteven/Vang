#pragma once

#include "Vang/Window/Window.h"

#include "GLFW/glfw3.h"

class VangInst;

namespace Vang {

	class WindowGLFW : public Window {
	public:
		WindowGLFW() = delete;
		WindowGLFW(VangInst& vangInst);
		WindowGLFW(VangInst& vangInst, std::string_view title);
		WindowGLFW(VangInst& vangInst, uint32_t width, uint32_t height);
		WindowGLFW(VangInst& vangInst, std::string_view title, uint32_t width, uint32_t height);
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

	private:
		void initializeWindow();
		static void resize(GLFWwindow* window, int width, int height);

		GLFWwindow* m_window;
	};

}