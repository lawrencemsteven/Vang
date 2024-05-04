#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"

#include "Vang/Utility/Time/Time.h"

#ifdef VANG_WINDOW_GLFW
#	include "GLFW/glfw3.h"
#endif

#ifdef VANG_BAKED_SHADERS
#	include VANG_SHADERS
#endif

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

	void GraphicsOpenGL::update() {
		glClear(GL_COLOR_BUFFER_BIT);
		m_shaderProgramManager.update();
	}

	void GraphicsOpenGL::windowResize(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}

	void GraphicsOpenGL::displayCamera(const Vang::Objects::Camera& camera) {
		m_shaderProgramManager.displayCamera(camera);
	}

	void GraphicsOpenGL::initialize() {
		initializeOpenGL();
		Vang::Windowing::Window& window = Vang::getWindow();
#ifdef VANG_BAKED_SHADERS
		m_shaderProgramManager.initialize(
			Vang::gfx::Shaders::SHADER_MAIN_VERT, Vang::gfx::Shaders::SHADER_MAIN_FRAG,
			Vang::gfx::Shaders::SHADER_VOXELRAYMARCHER, window.getWidth(), window.getHeight());
#else
		m_shaderProgramManager.initialize(
			static_cast<std::string>(VANG_SHADERS_FOLDER).append("/main.vert.glsl"),
			static_cast<std::string>(VANG_SHADERS_FOLDER).append("/main.frag.glsl"),
			static_cast<std::string>(VANG_SHADERS_FOLDER).append("/voxelRayMarcher.glsl"),
			window.getWidth(), window.getHeight());
#endif
	}

	void GraphicsOpenGL::initializeOpenGL() {
		VANG_DEBUG("Initializing OpenGL");

#ifdef VANG_WINDOW_GLFW
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			VANG_FATAL("Failed to initialize GLAD!");
		}
#endif

		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);

		Vang::Windowing::Window& window = Vang::getWindow();
		windowResize(window.getWidth(), window.getHeight());
	}

	void GraphicsOpenGL::cleanup() {
		VANG_DEBUG("Closing OpenGL");
	}
}
