#pragma once

namespace Vang::gfx {

	enum class ShaderType {
		Vertex,
		Fragment,
		Compute,
	};

	enum class ShaderDataType {
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool,
	};

	class ShaderProgram {
	public:
		ShaderProgram()								   = default;
		~ShaderProgram()							   = default;
		ShaderProgram(const ShaderProgram&)			   = delete;
		ShaderProgram(ShaderProgram&&)				   = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&)	   = delete;

		virtual bool linkProgram() = 0;
		virtual bool reloadShaders() = 0;
	};

}