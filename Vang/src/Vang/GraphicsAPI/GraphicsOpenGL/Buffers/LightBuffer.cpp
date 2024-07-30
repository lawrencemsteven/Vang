#include "LightBuffer.h"
#include "Vang.h"

namespace Vang::gfx::OpenGL {

	struct GPULight {
		glm::vec4 positionAndRadius{};
		glm::vec4 colorAndIntensity{};
	};

	void updateLight(const Vang::Utility::Light& light, const uint32_t index, GLuint buffer) {
		GPULight lightData{glm::vec4{light.getPosition(), light.getRadius()},
						   glm::vec4{light.getColor(), light.getIntensity()}};

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, index * sizeof(GPULight), sizeof(GPULight),
						&lightData);
	}

	LightBuffer::LightBuffer(ShaderProgram& shaderProgram) {
		shaderProgram.setUniform("LIGHT_COUNT", 0u);

		m_bufferLocation = glGetProgramResourceIndex(shaderProgram.getID(), GL_SHADER_STORAGE_BLOCK,
													 "SSBO_LIGHTS");
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_LIGHTS * sizeof(GPULight), NULL,
					 GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bufferLocation, m_buffer);
	}

	LightBuffer::~LightBuffer() {}

	void LightBuffer::update(ShaderProgram& shaderProgram) {
		auto& lightManager = Vang::getLightManager();
		const auto& lights = lightManager.getLights();

		// TODO: Grouping of lights will allow for better dirty testing (Also maybe better storage)
		// TODO: Light manager should be a linked list? Somehow a missing light needs to be filled
		// in or skipped.

		// If LightManager is dirty then update all lights
		if (lightManager.getDirty()) {
			shaderProgram.setUniform("LIGHT_COUNT", static_cast<uint32_t>(lights.size()));

			for (uint32_t i = 0; i < lights.size(); i++) {
				updateLight(lights[i], i, m_buffer);
				lightManager.cleanLight(i);
			}

			lightManager.setDirty(false);
			return;
		}

		// Check through each light to see if it is dirty
		for (uint32_t i = 0; i < lights.size(); i++) {
			if (lights[i].getDirty()) {
				updateLight(lights[i], i, m_buffer);
				lightManager.cleanLight(i);
			}
		}
	}
}