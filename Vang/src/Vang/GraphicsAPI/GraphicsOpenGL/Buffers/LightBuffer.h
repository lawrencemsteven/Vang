#pragma once

#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgram.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL {

	const std::size_t MAX_LIGHTS = 1000;

	class LightBuffer {
	public:
		LightBuffer() = default;
		LightBuffer(ShaderProgram& shaderProgram);
		~LightBuffer();

		void update(ShaderProgram& shaderProgram);

	private:
		GLint m_bufferLocation{};
		GLuint m_buffer{};
	};

}