#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	class Shader {
	public:
		Shader(std::filesystem::path path, ShaderType type);
		~Shader();
		Shader(const Shader&)			   = delete;
		Shader(Shader&&)				   = default;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&)	   = default;

		bool reload();

		std::optional<GLuint> getID();

	private:
		bool loadAndCompile();

		std::optional<GLuint> m_shader{};

		std::filesystem::path m_path{};
		ShaderType m_type;
	};

}