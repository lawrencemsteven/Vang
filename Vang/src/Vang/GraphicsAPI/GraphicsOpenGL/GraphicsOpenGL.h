#pragma once

#include "glad/glad.h"

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgramManager.h"

namespace Vang::gfx::OpenGL {

	class GraphicsOpenGL : public GraphicsAPI {
	public:
		GraphicsOpenGL();
		GraphicsOpenGL(std::string_view applicationName);
		~GraphicsOpenGL();
		GraphicsOpenGL(const GraphicsOpenGL&)			 = delete;
		GraphicsOpenGL(GraphicsOpenGL&&)				 = delete;
		GraphicsOpenGL& operator=(const GraphicsOpenGL&) = delete;
		GraphicsOpenGL& operator=(GraphicsOpenGL&&)		 = delete;

		void update() override;

		void windowResize(uint32_t width, uint32_t height) override;

		void displayCamera(const Camera& camera) override;

	private:
		void initialize();
		void cleanup();

		void initializeOpenGL();

		ShaderProgramManager m_shaderProgramManager;
	};

}
