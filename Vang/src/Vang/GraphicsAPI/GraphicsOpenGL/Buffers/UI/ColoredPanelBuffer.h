#pragma once

#include "Vang/GraphicsAPI/Generic/Buffers/UI/ColoredPanelBuffer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL::Buffers::UI {

	class ColoredPanelBuffer : public gfx::Generic::Buffers::UI::ColoredPanelBuffer {
		const std::size_t MAX_COLORED_PANELS = 1024;

	public:
		ColoredPanelBuffer() = default;
		~ColoredPanelBuffer();

		void initialize() override;
		void update() override;

		ColoredPanelID addPanel(const glm::vec2& topLeft, const glm::vec2& bottomRight,
								const float depth, const glm::vec4& color) override;

		void removePanel(ColoredPanelID idx) override;

	private:
		struct Point {
			glm::vec3 position{};
			glm::vec4 color{};
			glm::vec2 uv{};
		};

		std::vector<Point> m_data = std::vector<Point>(
			MAX_COLORED_PANELS, {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec4{0.0f, 0.0f, 0.0f, 0.0f},
								 glm::vec2{0.0f, 0.0f}});
		std::vector<glm::uint16> m_indices = std::vector<glm::uint16>(MAX_COLORED_PANELS * 6, 0u);

		GLuint m_vertexArrayObject{};
		GLuint m_vertexBufferObject{};
		GLuint m_elementBufferObject{};

		float getPanelDepth(const glm::uint16 idx) const;
		glm::uint16 newPanelIndex(const float depth) const;

		void addVertices(const glm::uint16 idx, const glm::vec2& topLeft,
						 const glm::vec2& bottomRight, const float depth, const glm::vec4& color);
		void addIndices(const glm::uint16 idx, const float depth);
		void updateVBO(const glm::uint16 idx);
		void updateEBO(const glm::uint16 startElem, const glm::uint16 endElem);
		void shiftElementsRightFromIndex(const glm::uint16 elem_idx);
	};

}