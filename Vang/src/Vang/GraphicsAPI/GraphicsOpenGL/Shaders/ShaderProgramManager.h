#pragma once

#include "Vang/Utility/Camera/Camera.h"

#include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/BlockBuffer.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/EntityBuffer.h"
#include "ShaderProgram.h"
#include "ShaderTexture.h"
#include "VertexData.h"

namespace Vang::gfx::OpenGL {

	class ShaderProgramManager {
	public:
		ShaderProgramManager() = default;

		void initialize(std::filesystem::path vertexShaderFile,
						std::filesystem::path fragmentShaderFile,
						std::filesystem::path computeShaderFile, unsigned int width,
						unsigned int height);
		void initialize(const std::string& vertexShaderFile, const std::string& fragmentShaderFile,
						const std::string& computeShaderFile, unsigned int width,
						unsigned int height);

		void update();
		void displayCamera(const Vang::Objects::Camera& camera);

		ShaderProgram& getRasterShaderProgram();
		ShaderProgram& getComputeShaderProgram();

	private:
		unsigned int m_screenWidth{};
		unsigned int m_screenHeight{};
		ShaderProgram m_rasterShaderProgram;
		ShaderProgram m_computeShaderProgram;
		ShaderTexture m_screenTexture;
		EntityBuffer m_entityBuffer;
		BlockBuffer m_blockBuffer{};
		VertexData m_vertexData;

		// TODO: Remove This
		void initialize_impl();
	};

}