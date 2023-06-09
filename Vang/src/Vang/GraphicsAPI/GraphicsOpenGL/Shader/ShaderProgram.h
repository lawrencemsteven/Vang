#pragma once

#include "Vang/GraphicsAPI/GraphicsOpenGL/Shader/Shader.h"

namespace Vang::gfx::OpenGL {

	class ShaderProgram {
	public:
		ShaderProgram()								   = default;
		~ShaderProgram()							   = default;
		ShaderProgram(const ShaderProgram&)			   = delete;
		ShaderProgram(ShaderProgram&&)				   = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&)	   = delete;

		void setVertexShader(std::string_view filepath);
		void setFragmentShader(std::string_view filepath);

		void initialize();

	private:
		unsigned int m_shaderProgram{0};
		VertexShader m_vertexShader;
		FragmentShader m_fragmentShader;
		ComputeShader m_computeShader;
	};

}