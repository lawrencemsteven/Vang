#pragma once

#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgram.h"

namespace Vang::gfx::OpenGL {

	class BlockBuffer {
	public:
		BlockBuffer() = default;

		void initialize();

		void update();

	private:
		GLuint m_texture{};
	};

}