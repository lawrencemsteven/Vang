#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/GL_Shader.h"

namespace Vang::gfx::OpenGL {

	class GL_ShaderProgram : public ShaderProgram {
	public:
		GL_ShaderProgram();
		~GL_ShaderProgram()							   = default;
		GL_ShaderProgram(const GL_ShaderProgram&)	   = delete;
		GL_ShaderProgram(GL_ShaderProgram&&)		   = delete;
		GL_ShaderProgram& operator=(const GL_ShaderProgram&) = delete;
		GL_ShaderProgram& operator=(GL_ShaderProgram&&)	  = delete;

		bool linkProgram() override;

	private:
		void attachShader(GL_Shader& shader);

		GLuint m_shaderProgram;
	};

}