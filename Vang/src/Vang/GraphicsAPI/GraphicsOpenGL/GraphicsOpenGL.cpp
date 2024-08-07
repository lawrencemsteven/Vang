#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"

#include "Vang/Utility/Time/Time.h"

#ifdef VANG_WINDOW_GLFW
#	include "GLFW/glfw3.h"
#	include "GraphicsOpenGL.h"
#endif

#ifdef VANG_BAKED_SHADERS
#	include VANG_SHADERS
#endif

namespace Vang::gfx::OpenGL {

	GraphicsOpenGL::~GraphicsOpenGL() {
		cleanup();
	}

	void GraphicsOpenGL::initialize() {
		GraphicsAPI::initialize();
		initializeOpenGL();
	}

	void GraphicsOpenGL::initialize(std::string_view applicationName) {
		GraphicsAPI::initialize(applicationName);
		initializeOpenGL();
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

	void GraphicsOpenGL::initializeShaders() {
		Vang::Windowing::Window& window = Vang::getWindow();
#ifdef VANG_BAKED_SHADERS
		m_shaderProgramManager.initialize(Vang::gfx::Shaders::BakedShaders::GET_MAIN_VERT(),
										  Vang::gfx::Shaders::BakedShaders::GET_MAIN_FRAG(),
										  Vang::gfx::Shaders::BakedShaders::GET_VOXELRAYMARCHER(),
										  window.getWidth(), window.getHeight());
#else
		m_shaderProgramManager.initialize(
			static_cast<std::filesystem::path>(VANG_SHADERS_FOLDER).append("main.vert.glsl"),
			static_cast<std::filesystem::path>(VANG_SHADERS_FOLDER).append("main.frag.glsl"),
			static_cast<std::filesystem::path>(VANG_SHADERS_FOLDER).append("voxelRayMarcher.glsl"),
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

		initializeShaders();
	}

	void GraphicsOpenGL::cleanup() {
		VANG_DEBUG("Closing OpenGL");
	}
}
