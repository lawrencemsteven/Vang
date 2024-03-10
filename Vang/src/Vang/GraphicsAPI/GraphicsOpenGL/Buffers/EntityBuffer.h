#pragma once

#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgram.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL {

	const std::size_t MAX_ENTITIES = 1000;

	class EntityBuffer {
	public:
		EntityBuffer(ShaderProgram& shader);
		~EntityBuffer();

		void update(ShaderProgram& shaderProgram);

	private:
		GLint m_bufferLocation{};
		GLuint m_buffer{};
	};

}