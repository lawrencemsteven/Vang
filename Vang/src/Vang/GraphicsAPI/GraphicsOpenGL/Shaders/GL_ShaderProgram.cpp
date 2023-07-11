#include "GL_ShaderProgram.h"

#include "GL_Shader.h"

namespace Vang::gfx::OpenGL {

	GL_ShaderProgram::GL_ShaderProgram()
		: m_shaderProgram{glCreateProgram()} {}

	void GL_ShaderProgram::attachShader(Shader& shader) {
		int shader_id{};
		if (const auto shader_id_opt = shader.getID(); shader_id_opt.has_value()) {
			shader_id = shader_id_opt.value();
		}
		else {
			VANG_ERROR("Shader is not initialized!");
			return;
		}

		glAttachShader(m_shaderProgram, shader_id);
	}

	std::optional<void> GL_ShaderProgram::linkProgram() { 
		glLinkProgram(m_shaderProgram);

		int success;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) { 
			char info_log[512];
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, info_log);
			VANG_ERROR("ShaderProgram Linking Failed!");
			VANG_ERROR(info_log);
			return std::nullopt;
		}

		return;
	}

}