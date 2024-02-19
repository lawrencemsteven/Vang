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

	class ShaderTexture3D {
	public:
		ShaderTexture3D() = default;
		~ShaderTexture3D();
		ShaderTexture3D(const ShaderTexture3D&)			   = delete;
		ShaderTexture3D(ShaderTexture3D&&)				   = delete;
		ShaderTexture3D& operator=(const ShaderTexture3D&) = delete;
		ShaderTexture3D& operator=(ShaderTexture3D&&)	   = delete;

		void initialize(unsigned int width, unsigned int height, unsigned int depth);

	private:
		GLuint m_texture{};
	};

}