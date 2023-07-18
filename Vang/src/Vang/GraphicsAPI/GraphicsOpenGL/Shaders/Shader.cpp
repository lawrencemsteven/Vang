#include "Shader.h"

#include "Vang/Utility/FileIO/FileIO.h"

namespace Vang::gfx::OpenGL {

	Shader::Shader(std::filesystem::path path, ShaderType type)
		: m_path{std::move(path)},
		  m_type{type} {
		loadAndCompile();
	}

	Shader::~Shader() {
		if (m_shader.has_value()) { glDeleteShader(m_shader.value()); }
	}

	bool Shader::reload() { return loadAndCompile(); }

	std::optional<GLuint> Shader::getID() { return m_shader; }

	bool Shader::loadAndCompile() {
		// Read From File
		std::string shader_source;
		if (const auto file_info = Vang::FileIO::readFile(m_path); file_info.has_value()) {
			shader_source = file_info.value();
		}
		else {
			VANG_ERROR("Shader File Could Not Be Read.");
			return false;
		}

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
		return true;
	}

}