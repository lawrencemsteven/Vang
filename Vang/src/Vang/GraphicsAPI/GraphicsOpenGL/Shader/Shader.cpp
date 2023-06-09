#include "Vang/GraphicsAPI/GraphicsOpenGL/Shader/Shader.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	void Shader::compileType(unsigned int type) {
		if (!hasSource()) { return; }

		m_shader		  = glCreateShader(type);
		const char* c_str = m_shaderSource.c_str();

		glShaderSource(m_shader, 1, &c_str, NULL);
		glCompileShader(m_shader);

		int success;
		char info_log[512];
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(m_shader, 512, NULL, info_log);
			VANG_ERROR("ERROR::SHADER::COMPILATION_FAILED");
			VANG_FATAL(info_log);
		}
	}

	void VertexShader::compile() { compileType(GL_VERTEX_SHADER); }

	void FragmentShader::compile() { compileType(GL_FRAGMENT_SHADER); }

	void ComputeShader::compile() { compileType(GL_COMPUTE_SHADER); }

};