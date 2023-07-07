#include "Shader.h"

namespace Vang::gfx::OpenGL {

	GL_Shader::GL_Shader(std::filesystem::path path, ShaderType type)
		: Shader{path, type} {}

	std::optional<void> GL_Shader::reload() { return loadAndCompile(); }

	std::optional<void> GL_Shader::loadAndCompile() {
		std::string shader_source;
		std::ifstream fileStream{m_path};

		// Read From File
		if (!fileStream.is_open()) {
			VANG_ERROR("Could not read file!");
			return std::nullopt;
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			shader_source.append(line + "\n");
		}

		fileStream.close();

		// Create Shader
		switch (m_type) {
			case ShaderType::Vertex:
				m_shader = std::make_optional<GLint>(glCreateShader(GL_VERTEX_SHADER));
				break;
			case ShaderType::Fragment:
				m_shader = std::make_optional<GLint>(glCreateShader(GL_FRAGMENT_SHADER));
				break;
			case ShaderType::Compute:
				m_shader = std::make_optional<GLint>(glCreateShader(GL_COMPUTE_SHADER));
				break;
		}

		// Compile Shader
		const char* shader_source_char = shader_source.c_str();
		glShaderSource(m_shader.value(), 1, &shader_source_char, NULL);
		glCompileShader(m_shader.value());

		// Check For Compilation Errors
		int success;
		char info_log[512];
		glGetShaderiv(m_shader.value(), GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(m_shader.value(), 512, NULL, info_log);
			VANG_ERROR("ERROR::SHADER::COMILATION_FAILED");
			VANG_ERROR(info_log);
		}
	}

}

/* namespace Vang::gfx::OpenGL {

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

};*/