#pragma once

#include "Vang/Utility/Camera/Camera.h"

#include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/BlockBuffer.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/EntityBuffer.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/LightBuffer.h"
#include "ShaderProgram.h"
#include "ShaderTexture.h"
#include "VertexData.h"

namespace Vang::gfx::OpenGL {

	class ShaderProgramManager {
	public:
		ShaderProgramManager() = default;

		void initialize(std::filesystem::path vertexShaderFile,
						std::filesystem::path fragmentShaderFile,
						std::filesystem::path computeShaderFile);
		void initialize(const std::string& vertexShaderFile, const std::string& fragmentShaderFile,
						const std::string& computeShaderFile);

		double getRenderTextureScale() const;

		void setRenderTextureScale(const double renderTextureScale);

		void update();
		void displayCamera(const Vang::Objects::Camera& camera);

		void resizeRenderTexture();

		ShaderProgram& getRasterShaderProgram();
		ShaderProgram& getComputeShaderProgram();

	private:
		double m_renderTextureScale{1.0};
		ShaderProgram m_rasterShaderProgram;
		ShaderProgram m_computeShaderProgram;
		ShaderTexture m_screenTexture;
		EntityBuffer m_entityBuffer;
		LightBuffer m_lightBuffer;
		BlockBuffer m_blockBuffer{};
		VertexData m_vertexData;

		// TODO: Remove This
		void initialize_impl();

		const std::pair<uint32_t, uint32_t> getRenderResolution() const;
	};

}