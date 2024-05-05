#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {

	// TODO: Remove Path Variable When String
	class Shader {
	public:
		Shader(std::filesystem::path path, ShaderType type);
		Shader(const char* src, ShaderType type);
		~Shader();
		Shader(const Shader&)			 = delete;
		Shader(Shader&&)				 = default;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&)		 = default;

		bool reload();

		std::optional<GLuint> getID();

	private:
		// TODO: Remove duplicated code
		bool loadAndCompile();
		bool loadAndCompile(const char* src);

		std::optional<GLuint> m_shader{};

		std::filesystem::path m_path{};
		ShaderType m_type;
	};

}