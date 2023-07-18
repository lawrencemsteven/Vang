#pragma once

#include "glad/glad.h"

namespace Vang::gfx::OpenGL {
	
	class VertexData {
	public:
		VertexData() = default;
		~VertexData();

		void initialize();
		void update();

	private:
		GLuint m_vertexArrayObject{};
		GLuint m_vertexBufferObject{};
	};

}