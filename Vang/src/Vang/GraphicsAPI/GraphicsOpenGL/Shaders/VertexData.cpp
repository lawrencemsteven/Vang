#include "VertexData.h"

namespace Vang::gfx::OpenGL {

	VertexData::~VertexData() {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		glDeleteBuffers(1, &m_vertexBufferObject);
	}

	void VertexData::initialize() {
		// vec3 pos
		// vec4 uv
		// clang-format off
		float vertices[9 * 4] = {
			-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Top Left
			 1.0f,	1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// Top Right
			-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// Bottom Left
			 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// Bottom Right
		};
		// clang-format on

		glGenVertexArrays(1, &m_vertexArrayObject);
		glGenBuffers(1, &m_vertexBufferObject);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
		// configure vertex attributes(s).
		glBindVertexArray(m_vertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
							  (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
							  (void*)(7 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexData::update() {
		glBindVertexArray(m_vertexArrayObject);

		GLenum err{};
		if ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL Error Update Mid: " << err << std::endl;
		}
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

}