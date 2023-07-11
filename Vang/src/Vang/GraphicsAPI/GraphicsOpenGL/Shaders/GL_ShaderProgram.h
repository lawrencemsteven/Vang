#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"

namespace Vang::gfx::OpenGL {

	class GL_ShaderProgram : public ShaderProgram {
	public:
		GL_ShaderProgram();
		~GL_ShaderProgram()							   = default;
		GL_ShaderProgram(const GL_ShaderProgram&)	   = delete;
		GL_ShaderProgram(GL_ShaderProgram&&)		   = delete;
		GL_ShaderProgram& operator=(const GL_ShaderProgram&) = delete;
		GL_ShaderProgram& operator=(GL_ShaderProgram&&)	  = delete;

		void attachShader(Shader& shader) override;
		std::optional<void> linkProgram() override;

	private:
		GLuint m_shaderProgram;
	};

}