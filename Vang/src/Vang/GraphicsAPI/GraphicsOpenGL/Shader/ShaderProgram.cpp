#include "Vang/GraphicsAPI/GraphicsOpenGL/Shader/ShaderProgram.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	void ShaderProgram::setVertexShader(std::string_view filepath) {
		m_vertexShader.loadFromFile(filepath);
	}

	void ShaderProgram::setFragmentShader(std::string_view filepath) {
		m_fragmentShader.loadFromFile(filepath);
	}

	void ShaderProgram::initialize() {
		m_vertexShader.compile();
		m_fragmentShader.compile();
		m_computeShader.compile();

		m_shaderProgram = glCreateProgram();
		if (m_vertexShader.hasSource()) glAttachShader(m_shaderProgram, m_vertexShader.getID());
		if (m_fragmentShader.hasSource()) glAttachShader(m_shaderProgram, m_fragmentShader.getID());
		if (m_computeShader.hasSource()) glAttachShader(m_shaderProgram, m_computeShader.getID());
		glLinkProgram(m_shaderProgram);

		int success;
		char infoLog[512];
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			VANG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED");
			VANG_FATAL(infoLog);
		}
	}

}