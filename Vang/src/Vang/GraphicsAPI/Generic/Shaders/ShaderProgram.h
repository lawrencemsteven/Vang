#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/Shader.h"

namespace Vang::gfx {

	class ShaderProgram {
	public:
		ShaderProgram()								   = default;
		~ShaderProgram()							   = default;
		ShaderProgram(const ShaderProgram&)			   = delete;
		ShaderProgram(ShaderProgram&&)				   = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&)	   = delete;

		virtual void attachShader(Shader& shader)  = 0;
		virtual std::optional<void> linkProgram() = 0;
	};

}