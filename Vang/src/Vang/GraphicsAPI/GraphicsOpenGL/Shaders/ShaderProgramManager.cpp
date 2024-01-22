#include "ShaderProgramManager.h"

#include "Vang/Utility/Time/Time.h"

namespace Vang::gfx::OpenGL {

	void ShaderProgramManager::initialize(std::filesystem::path vertexShaderFile,
										  std::filesystem::path fragmentShaderFile,
										  std::filesystem::path computeShaderFile,
										  unsigned int width, unsigned int height) {
		m_screenWidth  = width;
		m_screenHeight = height;
		m_screenTexture.initialize(width, height);
		m_vertexData.initialize();

		m_rasterShaderProgram.initialize();
		m_computeShaderProgram.initialize();

		Shader vertexShader{vertexShaderFile, ShaderType::Vertex};
		Shader fragmentShader{fragmentShaderFile, ShaderType::Fragment};
		m_rasterShaderProgram.attachShader(std::move(vertexShader));
		m_rasterShaderProgram.attachShader(std::move(fragmentShader));
		m_rasterShaderProgram.linkProgram();

		Shader computeShader{computeShaderFile, ShaderType::Compute};
		m_computeShaderProgram.attachShader(std::move(computeShader));
		m_computeShaderProgram.linkProgram();

		m_computeShaderProgram.setUniform("iResolution", static_cast<int>(width),
										  static_cast<int>(height));

		// TEMP SHADER BUFFER ATTEMPT
		std::vector<uint32_t> testData{};
		testData.resize(524288);
		std::fill(testData.begin(), testData.end(), 1);
		for (uint32_t i = 0; i < 10; i++) {
			testData[i] = i;
		}

		GLint chunkBlockLocation;
		GLuint chunkBuffer;
		GLuint chunkBufferBindingPoint = 0;

		chunkBlockLocation = glGetUniformBlockIndex(m_computeShaderProgram.getID(), "ChunkBlock");

		glGenBuffers(1, &chunkBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, chunkBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, testData.size() * sizeof(uint32_t), testData.data(),
					 GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, chunkBufferBindingPoint, chunkBuffer);
		glShaderStorageBlockBinding(m_computeShaderProgram.getID(), chunkBlockLocation,
									chunkBufferBindingPoint);
	}

	void ShaderProgramManager::update() {
		m_computeShaderProgram.setUniform("iTime", Vang::Utility::Time::timeSinceStart());

		m_computeShaderProgram.use();
		glDispatchCompute(floor(m_screenWidth / 16.0f), floor(m_screenHeight / 8.0f), 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		m_rasterShaderProgram.use();
		m_vertexData.update();
	}

	void ShaderProgramManager::displayCamera(const Vang::Objects::Camera& camera) {
		// Camera Position
		const glm::vec3 camera_position = camera.getPosition();
		m_computeShaderProgram.setUniform("camera.position", camera_position.x, camera_position.y,
										  camera_position.z);

		// Camera Orientation
		const glm::mat4 view = camera.getView();
		m_computeShaderProgram.setUniform("camera.forward", view[0][2], view[1][2], view[2][2]);
		m_computeShaderProgram.setUniform("camera.up", view[0][1], view[1][1], view[2][1]);
		m_computeShaderProgram.setUniform("camera.right", view[0][0], view[1][0], view[2][0]);

		// Camera FOV
		m_computeShaderProgram.setUniform("camera.fov", camera.getFOV());
	}

	ShaderProgram& ShaderProgramManager::getRasterShaderProgram() {
		return m_rasterShaderProgram;
	}

	ShaderProgram& ShaderProgramManager::getComputeShaderProgram() {
		return m_computeShaderProgram;
	}

}