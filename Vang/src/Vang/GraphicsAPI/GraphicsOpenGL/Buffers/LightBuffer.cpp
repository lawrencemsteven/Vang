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
		// TODO: Currently, only 1 Light will work at a time. The data is not being correctly sent
		// to the GPU.
		shaderProgram.setUniform("LightCount", 0u);

		m_bufferLocation =
			glGetProgramResourceIndex(shaderProgram.getID(), GL_SHADER_STORAGE_BLOCK, "Lights");
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_LIGHTS * sizeof(GPULight), NULL,
					 GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bufferLocation, m_buffer);
	}

	LightBuffer::~LightBuffer() {}

	void LightBuffer::update(ShaderProgram& shaderProgram) {
		auto LightManager = Vang::getLightManager();
		auto Lights		  = LightManager.getLights();

		// TODO: Optimize setting all Lights at once
		// If LightManager is dirty then set all Lights
		if (LightManager.getDirty()) {
			shaderProgram.setUniform("LightCount", static_cast<uint32_t>(Lights.size()));
			for (uint32_t i = 0; i < Lights.size(); i++) {
				updateLight(Lights[i], i, m_buffer);
				Lights[i].setDirty(false);
			}
			return;
		}

		// Sets dirty Lights on the GPU
		for (uint32_t i = 0; i < Lights.size(); i++) {
			if (Lights[i].getDirty()) {
				if (Lights[i].getDirty()) {
					updateLight(Lights[i], i, m_buffer);
					Lights[i].setDirty(false);
				}
			}
		}
	}
}