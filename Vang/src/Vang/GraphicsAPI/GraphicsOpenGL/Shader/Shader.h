#pragma once

#include "Vang/GraphicsAPI/Generic/Shader/Shader.h"

namespace Vang::gfx::OpenGL {

	class GL_Shader : public Shader {
	public:
		GL_Shader()							   = delete;
		~GL_Shader()						   = default;
		GL_Shader(const GL_Shader&)			   = delete;
		GL_Shader(GL_Shader&&)				   = delete;
		GL_Shader& operator=(const GL_Shader&) = delete;
		GL_Shader& operator=(GL_Shader&&)	   = delete;

		GL_Shader(std::filesystem::path path, ShaderType type);

		std::optional<void> reload() override;

	private:
		std::optional<void> loadAndCompile() override;

		std::optional<GLint> m_shader{};
	};

}

#include "glad/glad.h"

/*#include "Vang/GraphicsAPI/Generic/Shader/Shader.h"

namespace Vang::gfx::OpenGL {

	class Shader {
	public:
		Shader()						 = default;
		~Shader()						 = default;
		Shader(const Shader&)			 = delete;
		Shader(Shader&&)				 = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&)		 = delete;

		Shader(std::string_view shader_source)
			: m_shaderSource{shader_source} {}

		void setSource(std::string_view shader_source) { m_shaderSource = shader_source; }
		std::string_view getSource() { return m_shaderSource; }
		void loadFromFile(std::string_view filepath) {
			m_shaderSource.clear();
			std::ifstream fileStream{filepath.data()};

			if (!fileStream.is_open()) { VANG_FATAL("Could not read file!"); }

			std::string line = "";
			while (!fileStream.eof()) {
				std::getline(fileStream, line);
				m_shaderSource.append(line + "\n");
			}

			fileStream.close();
		}
		bool hasSource() { return !m_shaderSource.empty(); }
		unsigned int getID() { return m_shader; }

	protected:
		std::string m_shaderSource;
		unsigned int m_shader{0};

		void compileType(unsigned int type);

		virtual void compile() = 0;
	};

	class VertexShader : public Shader {
	public:
		VertexShader()								 = default;
		~VertexShader()								 = default;
		VertexShader(const VertexShader&)			 = delete;
		VertexShader(VertexShader&&)				 = delete;
		VertexShader& operator=(const VertexShader&) = delete;
		VertexShader& operator=(VertexShader&&)		 = delete;

		VertexShader(std::string_view shader_source)
			: Shader{shader_source} {}

		void compile() override;
	};

	class FragmentShader : public Shader {
	public:
		FragmentShader()								 = default;
		~FragmentShader()								 = default;
		FragmentShader(const FragmentShader&)			 = delete;
		FragmentShader(FragmentShader&&)				 = delete;
		FragmentShader& operator=(const FragmentShader&) = delete;
		FragmentShader& operator=(FragmentShader&&)		 = delete;

		FragmentShader(std::string_view shader_source)
			: Shader{shader_source} {}

		void compile() override;
	};

	class ComputeShader : public Shader {
	public:
		ComputeShader()								   = default;
		~ComputeShader()							   = default;
		ComputeShader(const ComputeShader&)			   = delete;
		ComputeShader(ComputeShader&&)				   = delete;
		ComputeShader& operator=(const ComputeShader&) = delete;
		ComputeShader& operator=(ComputeShader&&)	   = delete;

		ComputeShader(std::string_view shader_source)
			: Shader{shader_source} {}

		void compile() override;
	};

}*/