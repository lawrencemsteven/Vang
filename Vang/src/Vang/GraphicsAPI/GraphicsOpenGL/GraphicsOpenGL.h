#pragma once

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Shader/ShaderProgram.h"

class VangInst;

namespace Vang::gfx::OpenGL {

	class GraphicsOpenGL : public GraphicsAPI {
	public:
		GraphicsOpenGL() = delete;
		GraphicsOpenGL(VangInst& vangInst);
		GraphicsOpenGL(VangInst& vangInst, std::string_view applicationName);
		~GraphicsOpenGL();
		GraphicsOpenGL(const GraphicsOpenGL&)			 = delete;
		GraphicsOpenGL(GraphicsOpenGL&&)				 = delete;
		GraphicsOpenGL& operator=(const GraphicsOpenGL&) = delete;
		GraphicsOpenGL& operator=(GraphicsOpenGL&&)		 = delete;

		void beginFrame() override;

		void windowResize(uint32_t width, uint32_t height) override;

	private:
		void initialize();
		void cleanup();

		void initializeOpenGL();
		void initializeShaders();

		ShaderProgram m_shaderProgram;
	};

}
