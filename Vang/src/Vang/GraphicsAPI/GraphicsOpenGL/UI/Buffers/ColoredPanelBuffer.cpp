#include "ColoredPanelBuffer.h"

namespace Vang::gfx::OpenGL::UI::Buffers {

	ColoredPanelBuffer::~ColoredPanelBuffer() {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		glDeleteBuffers(1, &m_vertexBufferObject);
	}

	void ColoredPanelBuffer::initialize() {
		// Top Left
		m_data[0] = Point{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec4{1.0f, 1.0f, 1.0f, 0.5f},
						  glm::vec2{0.0f, 1.0f}};
		// Top Right
		m_data[1] = Point{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec4{0.0f, 1.0f, 0.0f, 0.5f},
						  glm::vec2{1.0f, 1.0f}};
		// Bottom Left
		m_data[2] = Point{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 0.5f},
						  glm::vec2{0.0f, 0.0f}};
		// Bottom Right
		m_data[3] = Point{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 1.0f, 0.5f},
						  glm::vec2{1.0f, 0.0f}};

		glGenVertexArrays(1, &m_vertexArrayObject);
		glGenBuffers(1, &m_vertexBufferObject);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
		// configure vertex attributes(s).
		glBindVertexArray(m_vertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(Point), m_data.data(), GL_STATIC_DRAW);

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

	void ColoredPanelBuffer::update() {
		glBindVertexArray(m_vertexArrayObject);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

}