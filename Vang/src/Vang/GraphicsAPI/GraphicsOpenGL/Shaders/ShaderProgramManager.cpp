#include "ShaderProgramManager.h"

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

		// Old Blocks
		// 0 - Air
		// 1 - Green
		// 4 - Yellow
		// 3 - Fog

		// Blocks
		// 0  - Air
		// 1  - Fog
		// 2  - Black
		// 3  - Gray
		// 4  - Light Gray
		// 5  - White
		// 6  - Red
		// 7  - Orange
		// 8  - Yellow
		// 9  - Green
		// 10 - Blue
		// 11 - Purple

		enum class Blocks {
			Air,
			Fog,
			Black,
			Gray,
			LightGray,
			White,
			Red,
			Orange,
			Yellow,
			Green,
			Blue,
			Purple,
		};

		// {x, y, z}
		// y - up

		// Logan
		// World& world = Vang::Voxel::getCurrentWorld();
		// void world.setBlock(glm::ivec3 position, Blocks block);
		// void world.setBlock(glm::ivec3{28, 1, 28}, 6);
		// world.generateDungion(startx, starty, length, width, height, Blocks living, Blocks Dead);

		// Ryan
		// World& world = Vang::Voxel::getCurrentWorld();
		// Blocks world.getBlock(glm::ivec3 position);
		// bool world.getSolid(glm::ivec3 position);
		// EntityManager& entityManager = Vang::getEntityManager();
		// entityManager.setEntityPosition(0, glm::vec3 position);
		// glm::mix(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, 0.1f);
		// Vang::getPlayer().getCamera().getPosition();

		// Steven
		// Hook up world update functions
		// Entity Manager
		// getBlock function
		// getSolid function
		// Make world 256x256x256

		// TEMP SHADER BUFFER ATTEMPT
		std::vector<uint32_t> testData{};
		std::vector<uint32_t> testData2{};
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

		// [5, 5, 5]
		testData[5 + 5 * 64 + 5 * 64 * 64] = 4;

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




		// 3D Textures
		uint32_t renderDistance = 1;
		uint32_t viewDistance	= 2 * (renderDistance - 1) + 1;
		glm::uvec3 chunkDistance{};
		for (uint32_t i = 0; i < 3; i++) {
			chunkDistance[i] = viewDistance * Vang::Voxel::chunkSize[i];
		}

		m_computeShaderProgram.setUniform("iRenderDistance", renderDistance);
		testData2.resize(std::max(viewDistance, 64u) * std::max(viewDistance, 64u) *
						 std::max(viewDistance, 64u));
		std::fill(testData2.begin(), testData2.end(), 2u);

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




		// Lights
		struct Light {
			glm::vec4 position;
			float range;
			float intensity;
		};

		std::vector<Light> lights{};
		lights.push_back(Light{glm::vec4{5.0f, 6.0f, 7.0f, 1.0f}, 15.0f, 1.0f});

		GLint lightsLocation;
		GLuint lightsBuffer;
		lightsLocation = glGetProgramResourceIndex(m_computeShaderProgram.getID(),
												   GL_SHADER_STORAGE_BLOCK, "Lights");
		glGenBuffers(1, &lightsBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightsBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, lights.size() * sizeof(Light), lights.data(),
					 GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, lightsLocation, lightsBuffer);




		// // Entities
		// struct Entity {
		// 	glm::vec4 position;
		// 	float radius;
		// };

		// std::vector<Entity> entities{};
		// entities.push_back(Entity{glm::vec4{5.5f, 5.5f, 5.5f, 1.0f}, 0.5f});
		// // entities.push_back(Entity{glm::vec4{5.0f, 5.0f, 8.0f, 1.0f}, 0.5f});

		// GLint entitiesLocation;
		// GLuint entitiesBuffer;
		// entitiesLocation = glGetProgramResourceIndex(m_computeShaderProgram.getID(),
		// 											 GL_SHADER_STORAGE_BLOCK, "Entities");
		// glGenBuffers(1, &entitiesBuffer);
		// glBindBuffer(GL_SHADER_STORAGE_BUFFER, entitiesBuffer);
		// glBufferData(GL_SHADER_STORAGE_BUFFER, entities.size() * sizeof(Entity), entities.data(),
		// 			 GL_DYNAMIC_DRAW);
		// glBindBufferBase(GL_SHADER_STORAGE_BUFFER, entitiesLocation, entitiesBuffer);
		m_entityBuffer = EntityBuffer{m_computeShaderProgram};
	}

	void ShaderProgramManager::update() {
		m_computeShaderProgram.setUniform("iTime", Vang::Utility::Time::timeSinceStart());

		m_computeShaderProgram.use();
		glDispatchCompute(static_cast<GLuint>(floor(m_screenWidth / 16.0f)),
						  static_cast<GLuint>(floor(m_screenHeight / 8.0f)), 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		m_entityBuffer.update(m_computeShaderProgram);
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