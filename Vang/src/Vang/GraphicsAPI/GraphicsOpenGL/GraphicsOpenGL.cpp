#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"
#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace Vang {

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst)
		: GraphicsAPI{vangInst} {
		initialize();
	}

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst, std::string_view applicationName)
		: GraphicsAPI{vangInst, applicationName} {
		initialize();
	}

	GraphicsOpenGL::~GraphicsOpenGL() { cleanup(); }

	void GraphicsOpenGL::beginFrame() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicsOpenGL::windowResize(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}

	void GraphicsOpenGL::initialize() {
		VANG_DEBUG("Initializing OpenGL");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			VANG_FATAL("Failed to initialize GLAD!");
		}

		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);

		windowResize(m_vangInst.getWindow().getWidth(), m_vangInst.getWindow().getHeight());
	}

	void GraphicsOpenGL::cleanup() { VANG_DEBUG("Closing OpenGL"); }

}
