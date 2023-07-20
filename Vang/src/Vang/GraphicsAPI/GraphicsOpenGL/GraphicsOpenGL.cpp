#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"

#include "Vang/Utility/Time/Time.h"

#ifdef VANG_WINDOW_GLFW
#	include "GLFW/glfw3.h"
#endif

#define DEFAULT_VERTEX_SHADER "../../../Vang/shaders/main.vert.glsl"
#define DEFAULT_FRAGMENT_SHADER "../../../Vang/shaders/main.frag.glsl"
#define DEFAULT_COMPUTE_SHADER "../../../Vang/shaders/voxelRayMarcher.glsl"

namespace Vang::gfx::OpenGL {

	GraphicsOpenGL::GraphicsOpenGL() {
		initialize();
	}

	GraphicsOpenGL::GraphicsOpenGL(std::string_view applicationName)
		: GraphicsAPI{applicationName} {
		initialize();
	}

	GraphicsOpenGL::~GraphicsOpenGL() {
		cleanup();
	}

	void GraphicsOpenGL::beginFrame() {
		glClear(GL_COLOR_BUFFER_BIT);
		m_shaderProgramManager.update();
	}

	void GraphicsOpenGL::endFrame() {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		Time::updateDeltaTime();
	}

	void GraphicsOpenGL::windowResize(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}

	void GraphicsOpenGL::displayCamera(const Camera& camera) {
		m_shaderProgramManager.displayCamera(camera);
	}

	void GraphicsOpenGL::initialize() {
		initializeOpenGL();
		Window& window = VangInst::Get().getWindow();
		m_shaderProgramManager.initialize(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER,
										  DEFAULT_COMPUTE_SHADER, window.getWidth(),
										  window.getHeight());
	}

	void GraphicsOpenGL::initializeOpenGL() {
		VANG_DEBUG("Initializing OpenGL");

#ifdef VANG_WINDOW_GLFW
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			VANG_FATAL("Failed to initialize GLAD!");
		}
#endif

		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);

		Window& window = VangInst::Get().getWindow();
		windowResize(window.getWidth(), window.getHeight());
	}

	void GraphicsOpenGL::cleanup() {
		VANG_DEBUG("Closing OpenGL");
	}

}
