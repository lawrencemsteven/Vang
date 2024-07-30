#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL::UI::Buffers {

	class ColoredPanelBuffer {
		const std::size_t MAX_COLORED_PANELS = 1000;

	public:
		ColoredPanelBuffer() = default;
		~ColoredPanelBuffer();

		void initialize();
		void update();

	private:
		struct Point {
			glm::vec3 position{};
			glm::vec4 color{};
			glm::vec2 uv{};
		};

		std::vector<Point> m_data{MAX_COLORED_PANELS,
								  {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec4{0.0f, 0.0f, 0.0f, 0.0f},
								   glm::vec2{0.0f, 0.0f}}};

		GLuint m_vertexArrayObject{};
		GLuint m_vertexBufferObject{};
	};

}