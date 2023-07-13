#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	class GL_Shader {
	public:
		GL_Shader()							   = delete;
		~GL_Shader();
		GL_Shader(const GL_Shader&)			   = delete;
		GL_Shader(GL_Shader&&)				   = delete;
		GL_Shader& operator=(const GL_Shader&) = delete;
		GL_Shader& operator=(GL_Shader&&)	   = delete;

		GL_Shader(std::filesystem::path path, ShaderType type);

		bool reload();

		std::optional<int> getID();

	private:
		bool loadAndCompile();

		std::optional<GLint> m_shader{};

		std::filesystem::path m_path{};
		ShaderType m_type;
	};

}