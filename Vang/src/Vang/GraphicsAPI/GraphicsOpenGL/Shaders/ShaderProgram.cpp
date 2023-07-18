#include "ShaderProgram.h"

#include "Shader.h"

namespace Vang::gfx::OpenGL {

	void ShaderProgram::initialize() {
		m_shaderProgram = glCreateProgram();
	}

	bool ShaderProgram::linkProgram() {
		glLinkProgram(m_shaderProgram);

		int success;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char info_log[512];
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, info_log);
			VANG_ERROR("ShaderProgram Linking Failed!");
			VANG_ERROR(info_log);
			return false;
		}

		return true;
	}

	bool ShaderProgram::reloadShaders() {
		for (auto& shader : m_attachedShaders) {
			if (!shader.reload()) {
				return false;
			}
		}
		reinitialize();
	}

	void ShaderProgram::reinitialize() {
		glDeleteProgram(m_shaderProgram);
		m_shaderProgram = glCreateProgram();
		linkProgram();
	}

	bool ShaderProgram::attachShader(Shader shader) {
		GLuint shader_id{};
		if (const auto shader_id_opt = shader.getID(); shader_id_opt.has_value()) {
			shader_id = shader_id_opt.value();
		}
		else {
			VANG_ERROR("Shader is not initialized!");
			return false;
		}

		glAttachShader(m_shaderProgram, shader_id);

		m_attachedShaders.push_back(std::move(shader));
		return true;
	}

	void ShaderProgram::use() {
		glUseProgram(m_shaderProgram);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::float32_t val1) {
		glProgramUniform1f(m_shaderProgram, getVarLocation(name), val1);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::float32_t val1,
								   glm::float32_t val2) {
		glProgramUniform2f(m_shaderProgram, getVarLocation(name), val1, val2);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::float32_t val1,
								   glm::float32_t val2, glm::float32_t val3) {
		glProgramUniform3f(m_shaderProgram, getVarLocation(name), val1, val2, val3);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::float32_t val1,
								   glm::float32_t val2, glm::float32_t val3, glm::float32_t val4) {
		glProgramUniform4f(m_shaderProgram, getVarLocation(name), val1, val2, val3, val4);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::int32_t val1) {
		glProgramUniform1i(m_shaderProgram, getVarLocation(name), val1);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2) {
		glProgramUniform2i(m_shaderProgram, getVarLocation(name), val1, val2);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2,
								   glm::int32_t val3) {
		glProgramUniform3i(m_shaderProgram, getVarLocation(name), val1, val2, val3);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2,
								   glm::int32_t val3, glm::int32_t val4) {
		glProgramUniform4i(m_shaderProgram, getVarLocation(name), val1, val2, val3, val4);
	}

	void ShaderProgram::setUniform(const std::string& name, bool val1) {
		glProgramUniform1i(m_shaderProgram, getVarLocation(name), val1);
	}

	GLuint ShaderProgram::getVarLocation(const std::string& name) {
		if (m_uniformVariables.find(name) != m_uniformVariables.end()) {
			return m_uniformVariables[name];
		}
		else {
			m_uniformVariables[name] = glGetUniformLocation(m_shaderProgram, name.c_str());
			return m_uniformVariables[name];
		}
	}
}