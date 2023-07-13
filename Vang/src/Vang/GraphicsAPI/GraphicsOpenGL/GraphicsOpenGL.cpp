#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"
#include "glad/glad.h"

#ifdef VANG_WINDOW_GLFW
#	include "GLFW/glfw3.h"
#endif

namespace Vang::gfx::OpenGL {

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst)
		: GraphicsAPI{vangInst} {
		initialize();
	}

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst, std::string_view applicationName)
		: GraphicsAPI{vangInst, applicationName} {
		initialize();
	}

	GraphicsOpenGL::~GraphicsOpenGL() { cleanup(); }

	void GraphicsOpenGL::beginFrame() { glClear(GL_COLOR_BUFFER_BIT); }

	void GraphicsOpenGL::windowResize(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}

	void GraphicsOpenGL::initialize() {
		initializeOpenGL();
		initializeShaders();
	}

	void GraphicsOpenGL::initializeOpenGL() {
		VANG_DEBUG("Initializing OpenGL");

#ifdef VANG_WINDOW_GLFW
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			VANG_FATAL("Failed to initialize GLAD!");
		}
#endif

		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);

		windowResize(m_vangInst.getWindow().getWidth(), m_vangInst.getWindow().getHeight());
	}

	void GraphicsOpenGL::initializeShaders() {
		//m_shaderProgram.setVertexShader("../../../Vang/shaders/main.vert.glsl");
		//m_shaderProgram.setFragmentShader("../../../Vang/shaders/main.frag.glsl");
		//m_shaderProgram.initialize();
	}

	void GraphicsOpenGL::cleanup() { VANG_DEBUG("Closing OpenGL"); }

}
