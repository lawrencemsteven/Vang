#include "ColoredPanelBuffer.h"

namespace Vang::gfx::OpenGL::Buffers::UI {

	ColoredPanelBuffer::~ColoredPanelBuffer() {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		glDeleteBuffers(1, &m_vertexBufferObject);
		glDeleteBuffers(1, &m_elementBufferObject);
	}

	void ColoredPanelBuffer::initialize() {
		glGenVertexArrays(1, &m_vertexArrayObject);
		glGenBuffers(1, &m_vertexBufferObject);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
		// configure vertex attributes(s).
		glBindVertexArray(m_vertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);

		glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(Point), nullptr, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uint16), nullptr,
					 GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
							  (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
							  (void*)(7 * sizeof(float)));
	}

	void ColoredPanelBuffer::update() {
		glBindVertexArray(m_vertexArrayObject);
		glDrawElements(GL_TRIANGLES, m_panelCount * 6, GL_UNSIGNED_SHORT, m_indices.data());
	}

	ColoredPanelBuffer::ColoredPanelID ColoredPanelBuffer::addPanel(const glm::vec2& topLeft,
																	const glm::vec2& bottomRight,
																	const float depth,
																	const glm::vec4& color) {
		if (m_panelCount >= MAX_COLORED_PANELS) {
			// TODO: Expand buffer size? Increase buffer size as panels are added?
			VANG_ERROR("Max number of colored panels reached in this menu!");
			return static_cast<ColoredPanelID>(MAX_COLORED_PANELS);
		}

		const glm::uint16 idx	   = 4 * m_panelCount;
		const glm::uint16 elem_idx = 6 * m_panelCount;

		addVertices(idx, topLeft, bottomRight, depth, color);

		addIndices(idx, depth);

		return static_cast<ColoredPanelID>(m_panelCount++);
	}

	void ColoredPanelBuffer::removePanel(ColoredPanelID idx) {
		// TODO: Actually remove the panel
		VANG_FATAL("ColoredPanelBuffer::removePanel not yet implemented!");
	}

	float ColoredPanelBuffer::getPanelDepth(const glm::uint16 idx) const {
		std::cout << "\t\tReturned Depth: " << m_data[idx * 6].position.z << " Index: " << idx
				  << std::endl;
		return m_data[m_indices[idx * 6]].position.z;
	}

	glm::uint16 ColoredPanelBuffer::newPanelIndex(const float depth) const {
		if (m_panelCount == 0) {
			return 0;
		}

		// Binary Search For New Panel At Provided Depth
		glm::uint16 minIdx = 0u;
		glm::uint16 midIdx;
		glm::uint16 maxIdx = m_panelCount - 1;

		std::cout << "\tDepth: " << depth << "\tMin Index: " << minIdx << "\tMax Index: " << maxIdx
				  << std::endl;

		if (depth > getPanelDepth(minIdx)) {
			std::cout << "\tAll The Way Left\n";
			return minIdx;
		}
		if (depth < getPanelDepth(maxIdx)) {
			std::cout << "\tAll The Way Right\n";
			return maxIdx + 1;
		}
		if (maxIdx - minIdx <= 1) {
			return 1;
		}

		// If panel has same value as another panel then it should be placed on the left.
		while (maxIdx - minIdx > 1) {
			midIdx = static_cast<glm::uint16>(static_cast<float>(maxIdx - minIdx) / 2.0f) + minIdx;
			std::cout << "\tMin Index: " << minIdx << "\tMid Index: " << midIdx
					  << "\tMax Index: " << maxIdx << std::endl;

			if (depth < getPanelDepth(midIdx)) {
				minIdx = midIdx;
			}
			else {
				maxIdx = midIdx;
			}
		}

		return maxIdx;
	}

	void ColoredPanelBuffer::addVertices(const glm::uint16 idx, const glm::vec2& topLeft,
										 const glm::vec2& bottomRight, const float depth,
										 const glm::vec4& color) {
		// Top Left
		m_data[idx].position = glm::vec3{topLeft, depth};
		m_data[idx].color	 = color;
		m_data[idx].uv		 = glm::vec2{0.0f, 1.0f};

		// Top Right
		m_data[idx + 1].position = glm::vec3{bottomRight.x, topLeft.y, depth};
		m_data[idx + 1].color	 = color;
		m_data[idx + 1].uv		 = glm::vec2{0.0f, 1.0f};

		// Bottom Left
		m_data[idx + 2].position = glm::vec3{topLeft.x, bottomRight.y, depth};
		m_data[idx + 2].color	 = color;
		m_data[idx + 2].uv		 = glm::vec2{0.0f, 0.0f};

		// Bottom Right
		m_data[idx + 3].position = glm::vec3{bottomRight, depth};
		m_data[idx + 3].color	 = color;
		m_data[idx + 3].uv		 = glm::vec2{1.0f, 0.0f};

		updateVBO(idx);
	}

	void ColoredPanelBuffer::addIndices(const glm::uint16 idx, const float depth) {
		std::cout << "--------\n";
		const glm::uint16 new_idx = newPanelIndex(depth);

		std::cout << "New Index: " << new_idx << std::endl;

		for (int i = 0; i < m_panelCount + 1; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << m_indices[i * 6 + j] << " ";
			}
			std::cout << std::endl;
		}

		shiftElementsRightFromIndex(new_idx);

		// Assemble Elements
		m_indices[new_idx * 6]	   = idx;
		m_indices[new_idx * 6 + 1] = idx + 1;
		m_indices[new_idx * 6 + 2] = idx + 2;
		m_indices[new_idx * 6 + 3] = idx + 1;
		m_indices[new_idx * 6 + 4] = idx + 2;
		m_indices[new_idx * 6 + 5] = idx + 3;

		std::cout << "---\n";

		for (int i = 0; i < m_panelCount + 1; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << m_indices[i * 6 + j] << " ";
			}
			std::cout << std::endl;
		}

		updateEBO(new_idx, m_panelCount + 1);
	}

	void ColoredPanelBuffer::updateVBO(const glm::uint16 idx) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBindVertexArray(m_vertexArrayObject);
		glBufferSubData(GL_ARRAY_BUFFER, idx * sizeof(Point), 4 * sizeof(Point),
						m_data.data() + idx);
	}

	void ColoredPanelBuffer::updateEBO(const glm::uint16 startElem, const glm::uint16 endElem) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
		glBindVertexArray(m_vertexArrayObject);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, startElem * 6,
						(endElem - startElem) * 6 * sizeof(glm::uint16),
						m_indices.data() + startElem);
	}

	void ColoredPanelBuffer::shiftElementsRightFromIndex(const glm::uint16 elem_idx) {
		if (m_panelCount == 0) {
			return;
		}

		for (glm::uint16 i = m_panelCount; i > elem_idx; i--) {
			for (glm::uint16 j = 0; j < 6; j++) {
				m_indices[i * 6 + j] = m_indices[(i - 1) * 6 + j];
			}
		}
	}
}