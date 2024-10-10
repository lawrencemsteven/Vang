#pragma once

#include "glad/glad.h"

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgramManager.h"

namespace Vang::gfx::OpenGL {

	class GraphicsOpenGL : public GraphicsAPI {
	public:
		GraphicsOpenGL() = default;
		~GraphicsOpenGL();

		void initialize() override;
		void initialize(std::string_view applicationName);
		void update() override;
		void endUpdate() override;

		double getRenderTextureScale() const override;

		void setRenderTextureScale(const double renderTextureScale) override;

		void windowResize(uint32_t width, uint32_t height) override;
		void resizeRenderTexture() override;

		void displayCamera(const Vang::Objects::Camera& camera) override;

	private:
		void initializeOpenGL();
		void cleanup();

		void initializeShaders();

		ShaderProgramManager m_shaderProgramManager;
	};

}
