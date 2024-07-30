#include "ShaderProgramManager.h"
#include "Vang.h"

#include "Vang/Utility/Time/Time.h"
#include "Vang/Voxel/Chunk.h"

#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL {

	void ShaderProgramManager::initialize(std::filesystem::path vertexShaderFile,
										  std::filesystem::path fragmentShaderFile,
										  std::filesystem::path computeShaderFile,
										  unsigned int width, unsigned int height) {
		m_screenWidth  = width;
		m_screenHeight = height;
		m_screenTexture.initialize(width, height);
		m_vertexData.initialize();
		m_UIBuffers.initialize();

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

		initialize_impl();
	}

	void ShaderProgramManager::initialize(const std::string& vertexShaderFile,
										  const std::string& fragmentShaderFile,
										  const std::string& computeShaderFile, unsigned int width,
										  unsigned int height) {
		m_screenWidth  = width;
		m_screenHeight = height;
		m_screenTexture.initialize(width, height);
		m_vertexData.initialize();
		m_UIBuffers.initialize();

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

		m_rasterShaderProgram.setUniform("u_drawState", 0);

		initialize_impl();
	}

	void ShaderProgramManager::update() {
		m_computeShaderProgram.setUniform("iTime", Vang::Utility::Time::timeSinceStart());

		// TODO: Move this somewhere else
		const auto& raycastReturn = Vang::getPlayer().getRaycastResult();
		const glm::ivec4 selectedBlock =
			glm::ivec4{raycastReturn.blockHitPosition, raycastReturn.hit};
		m_computeShaderProgram.setUniform("selectedBlock", selectedBlock);

		m_blockBuffer.update();
		m_entityBuffer.update(m_computeShaderProgram);
		m_lightBuffer.update(m_computeShaderProgram);

		m_computeShaderProgram.use();
		glDispatchCompute(static_cast<GLuint>(floor(m_screenWidth / 16.0f)),
						  static_cast<GLuint>(floor(m_screenHeight / 8.0f)), 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		m_rasterShaderProgram.use();

		m_rasterShaderProgram.setUniform("u_drawState", 0);
		m_vertexData.update();

		glClear(GL_DEPTH_BUFFER_BIT);

		m_rasterShaderProgram.setUniform("u_drawState", 1);
		m_UIBuffers.update();

		glFlush();
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

	void ShaderProgramManager::initialize_impl() {
		// OpenGL Query
		// GLint max_layers;
		// glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_layers);
		// std::cout << "Max 3D Texture Size: " << max_layers << std::endl;
		// std::cout << "GL_DITHER: " << (glIsEnabled(GL_DITHER) == GL_TRUE) << std::endl;



		std::vector<uint32_t> testData2{};

		// 3D Textures
		uint32_t renderDistance = 1;
		uint32_t viewDistance	= 2 * (renderDistance - 1) + 1;
		glm::uvec3 chunkDistance{};
		for (uint32_t i = 0; i < 3; i++) {
			chunkDistance[i] = viewDistance * Vang::Voxel::CHUNK_SIZE[i];
		}

		m_computeShaderProgram.setUniform("iRenderDistance", renderDistance);
		testData2.resize(std::max(viewDistance, 64u) * std::max(viewDistance, 64u) *
						 std::max(viewDistance, 64u));
		std::fill(testData2.begin(), testData2.end(), 2u);

		m_blockBuffer.initialize();

		GLuint m_texture2{};
		glGenTextures(1, &m_texture2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_3D, m_texture2);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_R32UI, std::max(viewDistance, 64u),
					 std::max(viewDistance, 64u), std::max(viewDistance, 64u), 0, GL_RED_INTEGER,
					 GL_UNSIGNED_INT, testData2.data());
		glBindImageTexture(2, m_texture2, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32UI);

		GLenum err{};
		if ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << err << std::endl;
		}




		// OLD Lights
		// struct Light {
		// 	glm::vec4 position;
		// 	float range;
		// 	float intensity;
		// };

		// std::vector<Light> lights{};
		// lights.push_back(Light{glm::vec4{5.0f, 6.0f, 7.0f, 1.0f}, 15.0f, 1.0f});

		// GLint lightsLocation;
		// GLuint lightsBuffer;
		// lightsLocation = glGetProgramResourceIndex(m_computeShaderProgram.getID(),
		// 										   GL_SHADER_STORAGE_BLOCK, "Lights");
		// glGenBuffers(1, &lightsBuffer);
		// glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightsBuffer);
		// glBufferData(GL_SHADER_STORAGE_BUFFER, lights.size() * sizeof(Light), lights.data(),
		// 			 GL_DYNAMIC_DRAW);
		// glBindBufferBase(GL_SHADER_STORAGE_BUFFER, lightsLocation, lightsBuffer);

		m_entityBuffer = EntityBuffer{m_computeShaderProgram};
		m_lightBuffer  = LightBuffer{m_computeShaderProgram};
	}
}