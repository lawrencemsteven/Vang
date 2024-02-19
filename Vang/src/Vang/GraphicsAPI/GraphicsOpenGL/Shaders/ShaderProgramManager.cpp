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

		// OpenGL Query
		// GLint max_layers;
		// glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_layers);
		// std::cout << "Max 3D Texture Size: " << max_layers << std::endl;

		// TODO: NEED TO USE 3D TEXTURES INSTEAD OF AN SSBO

		// TEMP SHADER BUFFER ATTEMPT
		std::vector<uint32_t> testData{};
		testData.resize(262144);
		std::fill(testData.begin(), testData.end(), 0);

		// Ground plane
		for (uint32_t x = 0; x < 64; x++) {
			for (uint32_t z = 0; z < 64; z++) {
				testData[z * 64 + x] = 1;
			}
		}

		// [1, 5, 1]
		testData[1 + 1 * 64 + 5 * 64 * 64] = 1;

		for (uint32_t y = 25; y < 30; y++) {
			for (uint32_t x = 10; x < 15; x++) {
				for (uint32_t z = 10; z < 15; z++) {
					testData[x + z * 64 + y * 64 * 64] = 3;
				}
			}
		}
		for (uint32_t x = 11; x < 14; x++) {
			for (uint32_t z = 11; z < 14; z++) {
				testData[x + z * 64 + 30 * 64 * 64] = 3;
			}
		}
		for (uint32_t x = 12; x < 13; x++) {
			for (uint32_t z = 12; z < 13; z++) {
				testData[x + z * 64 + 31 * 64 * 64] = 3;
			}
		}

		// GLint chunkBlockLocation;
		// GLuint chunkBuffer;
		// GLuint chunkBufferBindingPoint = 0;
		// chunkBlockLocation = glGetUniformBlockIndex(m_computeShaderProgram.getID(), "ChunkBlock");
		// glGenBuffers(1, &chunkBuffer);
		// glBindBuffer(GL_SHADER_STORAGE_BUFFER, chunkBuffer);
		// glBufferData(GL_SHADER_STORAGE_BUFFER, testData.size() * sizeof(uint32_t), testData.data(),
		// 			 GL_DYNAMIC_DRAW);
		// glBindBufferBase(GL_SHADER_STORAGE_BUFFER, chunkBufferBindingPoint, chunkBuffer);
		// glShaderStorageBlockBinding(m_computeShaderProgram.getID(), chunkBlockLocation,
		// 							chunkBufferBindingPoint);

		GLuint m_texture{};
		glGenTextures(1, &m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_3D, m_texture);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_R32UI, 64, 64, 64, 0, GL_RED_INTEGER, GL_UNSIGNED_INT,
					 testData.data());
		glBindImageTexture(1, m_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32UI);

		GLenum err{};
		if ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "Uh oh 2! " << err << std::endl;
		}
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