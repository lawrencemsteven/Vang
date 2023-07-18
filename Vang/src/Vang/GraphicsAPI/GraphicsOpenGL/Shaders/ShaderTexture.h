#pragma once

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	class ShaderTexture {
	public:
		ShaderTexture() = default;
		~ShaderTexture();
		ShaderTexture(const ShaderTexture&)			   = delete;
		ShaderTexture(ShaderTexture&&)				   = delete;
		ShaderTexture& operator=(const ShaderTexture&) = delete;
		ShaderTexture& operator=(ShaderTexture&&)	   = delete;

		void initialize(unsigned int width, unsigned int height);

	private:
		GLuint m_texture{};
	};

}