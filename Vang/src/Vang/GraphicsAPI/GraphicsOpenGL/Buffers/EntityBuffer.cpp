#include "EntityBuffer.h"
#include "Vang.h"

namespace Vang::gfx::OpenGL {

	struct GPUEntity {
		glm::vec4 position{};
		float radius{0.5f};
	};

	void updateEntity(const Vang::Utility::Entity& entity, const uint32_t index, GLuint buffer) {
		GPUEntity entityData{glm::vec4(entity.getPosition(), 0.0f), entity.getRadius()};

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, index * sizeof(GPUEntity), sizeof(GPUEntity),
						&entityData);
	}

	EntityBuffer::EntityBuffer(ShaderProgram& shaderProgram) {
		// TODO: Currently, only 1 entity will work at a time. The data is not being correctly sent
		// to the GPU.
		shaderProgram.setUniform("entityCount", 0u);

		m_bufferLocation =
			glGetProgramResourceIndex(shaderProgram.getID(), GL_SHADER_STORAGE_BLOCK, "Entities");
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_ENTITIES * sizeof(GPUEntity), NULL,
					 GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bufferLocation, m_buffer);
	}

	EntityBuffer::~EntityBuffer() {}

	void EntityBuffer::update(ShaderProgram& shaderProgram) {
		auto entityManager = Vang::getEntityManager();
		auto entities	   = entityManager.getEntities();

		// TODO: Optimize setting all entities at once
		// If entityManager is dirty then set all entities
		if (entityManager.getDirty()) {
			shaderProgram.setUniform("entityCount", static_cast<uint32_t>(entities.size()));
			for (uint32_t i = 0; i < entities.size(); i++) {
				updateEntity(entities[i], i, m_buffer);
				entities[i].setDirty(false);
			}
			return;
		}

		// Sets dirty entities on the GPU
		for (uint32_t i = 0; i < entities.size(); i++) {
			if (entities[i].getDirty()) {
				if (entities[i].getDirty()) {
					updateEntity(entities[i], i, m_buffer);
					entities[i].setDirty(false);
				}
			}
		}
	}
}