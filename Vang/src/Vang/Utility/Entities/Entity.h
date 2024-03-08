#pragma once

#include "glm/glm.hpp"

namespace Vang::Utility {

	class Entity {
	public:
		Entity() = default;
		Entity(glm::vec4 position, const float radius);

		const glm::vec4& getPosition() const;
		float getRadius() const;

		void setPosition(glm::vec4 position);
		void setRadius(const float radius);

	private:
		glm::vec4 m_position{};
		float m_radius{};
	};

}