#pragma once

#include "Vang/Utility/Camera/Camera.h"

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
		VertexData m_vertexData;
	};

}